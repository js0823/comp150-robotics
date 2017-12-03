#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

static const std::string OPENCV_WINDOW = "Turtlebot Live";

// Detect all colors except walls.
int Lower_H = 0, Lower_S = 1, Lower_V = 1;
int Upper_H = 255, Upper_S = 255, Upper_V = 255;

class ImageDetector {
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Subscriber image_sub_depth_;
    image_transport::Publisher image_pub_;

  public:
    ImageDetector() 
        : it_(nh_) 
    {
        // Subscrive to input video feed and publish output video feed
        image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, 
            &ImageDetector::ColorDetectionCallBack, this);
        image_sub_depth_ = it_.subscribe("/camera/depth/image_raw", 1000, 
            &ImageDetector::DepthDetectionCallBack, this);
        image_pub_ = it_.advertise("/image_detector/output_video", 1);

        cv::namedWindow(OPENCV_WINDOW);
    }

    ~ImageDetector() {
        cv::destroyWindow(OPENCV_WINDOW);
    }

    void ColorDetectionCallBack(const sensor_msgs::ImageConstPtr &msg) {
        cv_bridge::CvImagePtr cv_ptr;

        try {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception &e) {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }

        cv::Mat img_mask, img_hsv;
        cv::cvtColor(cv_ptr->image, img_hsv, CV_BGR2HSV);
        cv::inRange(img_hsv,cv::Scalar(Lower_H, Lower_S, Lower_V),
            cv::Scalar(Upper_H,Upper_S,Upper_V),img_mask);

        // Remove small blobs which may be left over.
        cv::erode(img_mask, img_mask, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);
        cv::dilate(img_mask, img_mask, cv::Mat(), cv::Point(-1, -1), 2, 1, 1);

        // find contour and draw line around it.
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;

        findContours(img_mask, contours, hierarchy, 
            CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
        
        for (int i = 0; i < contours.size(); i++) {
            cv::drawContours(cv_ptr->image, contours, i, 
                cv::Scalar(0,0,0), 2, 8, hierarchy, 0, cv::Point());
        }
        
        // Update GUI Window
        cv::imshow(OPENCV_WINDOW, cv_ptr->image);
        //cv::imshow(OPENCV_WINDOW, img_mask);
        cv::waitKey(5);

        // Output modified video stream
        image_pub_.publish(cv_ptr->toImageMsg());
    }

    void DepthDetectionCallBack(const sensor_msgs::ImageConstPtr& msg) {
        //std::cout << "Top-left corner: " << *reinterpret_cast<const float*>
        //    (&msg->data[0]) << "m" << std::endl;
        
        cv_bridge::CvImageConstPtr cv_ptr;

        try {
            cv_ptr = cv_bridge::toCvShare(msg);
        }
        catch (cv_bridge::Exception &e) {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }
    }
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "image_detector");
    ImageDetector ic;
    ros::spin();
    return 0;
}