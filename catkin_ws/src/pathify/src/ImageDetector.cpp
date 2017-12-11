#include <ros/ros.h>
#include "std_msgs/String.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <pathify/ReturnCoordinate.h>
#include <sstream>

static const std::string OPENCV_WINDOW = "Turtlebot Live";

// Detect all colors except walls.
int Lower_H = 0, Lower_S = 1, Lower_V = 1;
int Upper_H = 255, Upper_S = 255, Upper_V = 255;

// Global stdout value
std::string previousString = "asd";

class ImageDetector {
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    //image_transport::Subscriber image_sub_depth_;
    image_transport::Publisher image_pub_;
    ros::Publisher imageDetector_pub;
    ros::Subscriber Input_Talker_sub;

  public:
    ImageDetector() 
        : it_(nh_) 
    {
        // Subscribe to input video feed and publish output video feed
        image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, 
            &ImageDetector::ColorDetectionCallBack, this);
        image_pub_ = it_.advertise("/image_detector/output_video", 1);

        // Output different messages for all to see.
        imageDetector_pub = nh_.advertise<std_msgs::String>("imageDetector_output", 1000);

        //Input_Talker_sub = nh_.subscribe("chatter", 1000, chatterCallback);

        cv::namedWindow(OPENCV_WINDOW);
    }

    ~ImageDetector() {
        cv::destroyWindow(OPENCV_WINDOW);
    }

    void chatterCallback(const std_msgs::String::ConstPtr &msg) {
        ROS_INFO("I heard: [%s]", msg->data.c_str());
    }

    bool ReturnCoordinate(pathify::ReturnCoordinate::Request &req, 
            pathify::ReturnCoordinate::Response &res) {
        
        // If no colors are found, return 0.0,0.0,0.0,
        res.coord_xyz = req.coord_x + "," + req.coord_y + "," + req.coord_z + ",";
        ROS_INFO("request: x=%s, y=%s, z=%s", req.coord_x.c_str(), req.coord_y.c_str(), req.coord_z.c_str());
        ROS_INFO("sending back response [%s]", res.coord_xyz.c_str());
        
        return true;
    }

    void ColorDetectionCallBack(const sensor_msgs::ImageConstPtr &msg) {
        cv_bridge::CvImagePtr cv_ptr;

        // Boolean values
        bool colorDetected = false;
        bool colorClose = false;

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

        if (!img_mask.empty()) {
            for (unsigned int i = 0;  i < contours.size();  i++) {
                if (cv::contourArea(contours[i]) >= 120000) {
                    //std::cout << "Area = " << cv::contourArea(contours[i]) << std::endl;
                    colorDetected = true;
                    colorClose = true;
                }
                else {
                    colorDetected = true;
                    colorClose = false;
                }
            }
        }
        else {
            colorDetected = false;
            colorClose = false;
        }

        if (colorDetected == true && colorClose == true) {
            if (previousString != "Stop") {
                std_msgs::String msg;
                std::stringstream ss;
                ss << "Stop";
                msg.data = ss.str();
                //std::cout << ss.str() << std::endl;

                ROS_INFO("%s", msg.data.c_str());
                imageDetector_pub.publish(msg);
                ss.clear();
                previousString = "Stop";
            }
        }
        else if (colorDetected == true && colorClose == false) {
            if (previousString != "FoundButGetCloser" && previousString != "Stop") {
                std_msgs::String msg;
                std::stringstream ss;
                ss << "FoundButGetCloser";
                msg.data = ss.str();
                //std::cout << ss.str() << std::endl;

                ROS_INFO("%s", msg.data.c_str());
                imageDetector_pub.publish(msg);
                ss.clear();
                previousString = "FoundButGetCloser";
            }
        }
        else {
            if (previousString != "NothingFound") {
                std_msgs::String msg;
                std::stringstream ss;
                ss << "NothingFound";
                msg.data = ss.str();
                //std::cout << ss.str() << std::endl;

                ROS_INFO("%s", msg.data.c_str());
                imageDetector_pub.publish(msg);
                ss.clear();
                previousString = "NothingFound";
            }
        }

        // Update GUI Window
        cv::imshow(OPENCV_WINDOW, cv_ptr->image);
        //cv::imshow(OPENCV_WINDOW, img_mask);
        cv::waitKey(5);

        // Output modified video stream
        image_pub_.publish(cv_ptr->toImageMsg());
    }
};

int main(int argc, char **argv) {
    ros::init(argc, argv, "image_detector");
    ImageDetector ic;
    ros::spin();
    return 0;
}