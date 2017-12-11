#include <ros/ros.h>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
#include <ctype.h>
#include <cstdlib>
#include "std_msgs/String.h"
#include <unistd.h>
#include "gazebo_msgs/SetModelState.h"
#include "gazebo_msgs/GetModelState.h"
#include "gazebo_msgs/ModelStates.h"
#include "gazebo_msgs/GetPhysicsProperties.h"
#include <actionlib/client/simple_action_client.h>
#include <nav2d_navigator/MoveToPosition2DAction.h>
#include <tf/transform_datatypes.h>
#include <nav2d_navigator/commands.h>

struct Coordinate
{
    float x;
    float y;
} botCoordinate;

struct Item
{
    std::string maze_name;
    std::string item_name;
    Coordinate location;
};

std::vector<Item> Robot_RAM;

/*output string format:
 *Maze Name;Item Name;Item x-location;Item y-location;Item z-location */
std::string Item_Information;
std::string message_from_openCV;

/*provided by the current maze name*/
std::string maze_name;
ros::ServiceClient client;
ros::Subscriber sub;
ros::Publisher chatter_pub;

bool found_before(std::string item_name);
bool is_empty(std::ifstream &pFile);
float string_to_float(std::string str);
Item parse_string_To_Item(std::string item_stringform);

std::string change_to_lowercase(std::string str);
std::string float_to_string(float flt);
std::vector<std::string> parse_input(std::string str);
std::vector<std::string> parse_output_from_ros(std::string str);
std::string parse_Item_To_string(Item item);

void go_mode(std::string item_name);
void find_mode(std::string item_name, ros::NodeHandle n);
void update_rom(const std::string &file_name, const std::string &content);
void update_ram(const std::string &filen_name);
void add_item_to_file(std::string item);
void chatterCallback(const std_msgs::String::ConstPtr &msg);

typedef actionlib::SimpleActionClient<nav2d_navigator::MoveToPosition2DAction> MoveClient;

int main(int argc, char **argv)
{

    bool end = false;
    update_ram("Robot_ROM.txt");
    maze_name = /*get from somewhere*/ "love";

    ros::init(argc, argv, "Input_Talker");
    ros::NodeHandle n;
    chatter_pub = n.advertise<std_msgs::String>("user_responds", 1000);
    //client = n.serviceClient<pathify::ReturnCoordinate>("coordinate");
    std::system("rosservice call /StartMapping");
    std::cout << "Attempting to localize...Please wait." << std::endl;
    sleep(20);
    std::cout << "Finished localizing." << std::endl;

    //ros::ServiceClient gmscl = n.serviceClient<gazebo_msgs::GetModelState>("/gazebo/get_model_states");
    //gazebo_msgs::GetModelState modelState;
    //modelState.request.model_name = "mobile_base";
    //modelState.request.relative_entity_name = "world";
    //gmscl.call(modelState);

    //geometry_msgs::Pose pose;
    //botCoordinate.x = modelState.response.pose.position.x;
    //botCoordinate.y = modelState.response.pose.position.y;
    //botCoordinate.z = modelState.response.pose.position.z;

    //tell the action client that we want to spin a thread by default
    //MoveBaseClient ac("goal", true);

    ////goal.target_pose.header.frame_id = "base_link";
    //goal.target_pose.header.frame_id = "map";
    //goal.target_pose.header.stamp = ros::Time::now();

    //goal.target_pose.pose.position.x = 1.0;
    //goal.target_pose.pose.position.y = 1.0;
    //goal.target_pose.pose.position.z = 0.000;
    //goal.target_pose.pose.orientation.w = 1.0;

    //ROS_INFO("Sending goal");
    //ac.sendGoal(goal);

    //ac.waitForResult();

    while (!end)
    {
        std::string input;
        std::cout << "What do you want me to do?"
                  << "\n";
        std::cout << "Commands are [go, find, quit]"
                  << "\n";
        std::cout << "Ex. Go to red ----> Will go to red if the red location is saved in the database."
                  << "\n";
        std::cout << "Ex. Find red ----> Will start exploring the map."
                  << "\n";
        std::cout << "Ex. quit, end, stop, terminate ----> Exit this program."
                  << "\n";
        getline(std::cin, input);
        std::vector<std::string> input_vector;
        input_vector = parse_input(input);
        int size = input_vector.size();

        if (size == 3) /*e.g "Go to LocationAA" */
        {
            if (change_to_lowercase(input_vector[0]) == "go")
            {
                if (!found_before(change_to_lowercase(input_vector[2])))
                {
                    std::cout << "Location not known. Should I find?"
                              << "\n";
                    std::cout << "y/n: ";
                    std::string responds;
                    getline(std::cin, responds);
                    std::vector<std::string> in;
                    in = parse_input(responds);
                    if (change_to_lowercase(in[0]) == "y")
                    {
                        find_mode(input_vector[2], n);
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    go_mode(input_vector[2]);
                }
            }
            else
            {
                std::cout << "I don't know that command! Maybe start with go."
                          << "\n";
            }
        }

        else if (size == 2) /*e.g,  "find locationAA" */
        {
            if (change_to_lowercase(input_vector[0]) == "find")
            {
                if (!found_before(change_to_lowercase(input_vector[1])))
                {
                    find_mode(input_vector[1], n);
                }
                else
                {
                    std::cout << " Location already found before. Should I go?"
                              << "\n";
                    std::cout << "y/n: ";
                    std::string responds;
                    getline(std::cin, responds);
                    std::vector<std::string> in;
                    in = parse_input(responds);
                    if (change_to_lowercase(in[0]) == "y")
                    {
                        go_mode(input_vector[1]);
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
            {
                std::cout << "I don't know that command! Maybe start with find."
                          << "\n";
            }
        }

        else if (size == 1)
        {
            if (change_to_lowercase(input_vector[0]) == "end" || change_to_lowercase(input_vector[0]) == "terminate" ||
                change_to_lowercase(input_vector[0]) == "stop" || change_to_lowercase(input_vector[0]) == "quit")
            {
                break; /*terminate program*/
            }
            else
            {
                std::cout << "I don't know that command!"
                          << "\n";
            }
        }

        else if (size <= 0 || size > 3)
        {
            std::cout << "Too many words! I understand up to three words per command!"
                      << "\n";
        }
    }
    std::cout << "Shutting Down ..."
              << "\n";
    std::cout << "Done! Have a great day!"
              << "\n";

    return 0;
}

void chatterCallback(const std_msgs::String::ConstPtr &msg)
{
    std::string s(msg->data.c_str());
    message_from_openCV = s;
    //ROS_INFO("I heard: [%s]", msg->data.c_str());
}

/* goes to the area name give*/
void go_mode(std::string item_name)
{
    int size = (int)Robot_RAM.size();
    for (int i = 0; i < size; i++)
    {
        if (Robot_RAM[i].item_name == item_name && Robot_RAM[i].maze_name == maze_name)
        {
            Coordinate x_y_z;
            x_y_z.x = Robot_RAM[i].location.x;
            x_y_z.y = Robot_RAM[i].location.y;

            MoveClient ac("MoveTo", true);
            while(!ac.waitForServer(ros::Duration(5.0))) {
                ROS_INFO("Waiting for the MoveTo action server to come up");
            }

            nav2d_navigator::MoveToPosition2DGoal goal;
	        goal.target_pose.x = x_y_z.x;
	        goal.target_pose.y = x_y_z.y;
	        //goal.target_pose.theta = tf::getYaw(msg->pose.orientation);
	        goal.target_distance = 0.25;
	        goal.target_angle = 0.1;
	
            ac.sendGoal(goal);
            ac.waitForResult();

            /* TODO: send xyz timi*/
            std::cout << "Going to "
                      << " " << item_name + "..."
                      << "\n";
            std::cout << "Goon to "
                      << " " << item_name + "!"
                      << "\n";
            return;
        }
    }
}

void find_mode(std::string item_name, ros::NodeHandle n)
{
    /*look for and add to memory*/
    Item tmp;
    bool found = false;
    tmp.maze_name = maze_name;
    tmp.item_name = change_to_lowercase(item_name);
    //pathify::ReturnCoordinate srv;
    std::system("rosservice call /StartExploration");

    while (!found)
    {
        sub = n.subscribe("imageDetector_output", 1000, chatterCallback);
        if (message_from_openCV == "Stop")
        {
            std::system("rosservice call /Stop");
            std::cout << " Is this the location? (y/n)"
                      << "\n";
            std::string responds;
            getline(std::cin, responds);
            std::vector<std::string> in;
            in = parse_input(responds);
            if (change_to_lowercase(in[0]) == "y")
            {
                /*TODO: get co-ordinated from timi*/
                found = true;
            }
            else if (change_to_lowercase(in[0]) == "n")
            {
                for (int i = 0; i < 4; i++)
                {
                    std_msgs::String msg;
                    std::stringstream ss;
                    ss << "keep_going";
                    msg.data = ss.str();
                    chatter_pub.publish(msg);
                }
            }
        }
    }

    /* if (client.call(srv))
     *    {
     *        /*recieve co-ordinate from robot*
     *        ROS_INFO("result: %s", srv.response.coord_xyz);
     *        std::string result = srv.response.coord_xyz;
     *        std::vector<std::string> tmp_result = parse_output_from_ros(result);
     *        Coordinate x_y_z;
     *        float size  = string_to_float(tmp_result[0]) + string_to_float(tmp_result[1]) + string_to_float(tmp_result[2]);
     *        if(size!= 0.0)
     *        {
     *            x_y_z.x =  string_to_float(tmp_result[0]);                           
     *            x_y_z.y =  string_to_float(tmp_result[1]);                          
     *            x_y_z.z =  string_to_float(tmp_result[2]);                          
     *            tmp.location = x_y_z;
     *            Robot_RAM.push_back(tmp);
     *            std::string tmp_string = parse_Item_To_string(tmp);
     *            update_rom("Robot_ROM.txt", tmp_string);
     *            std::cout<<"Found"<<" "<< item_name<<"\n";
}
}*/
}

void update_rom(const std::string &file_name, const std::string &content)
{
    std::ofstream outfile;
    outfile.open(file_name.c_str(), std::ios_base::app);
    if (outfile.is_open())
    {
        outfile << content;
        outfile.close();
        return;
    }
    std::cout << "could not save location to the memory"
              << "\n";
}

/*reads from file/database and updat RAM Memory*/
void update_ram(const std::string &file_name)
{
    std::string line;
    std::ifstream myfile(file_name.c_str());
    if (myfile.is_open())
    {
        if (!is_empty(myfile))
        {
            while (getline(myfile, line))
            {
                Item tmp = parse_string_To_Item(line);
                Robot_RAM.push_back(tmp);
            }
        }
        myfile.close();
    }
}

bool is_empty(std::ifstream &pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

std::string parse_Item_To_string(Item item)
{
    std::string fin;
    fin = item.maze_name + ";" + item.item_name + ";" + float_to_string(item.location.x) + ";" +
          float_to_string(item.location.y) + "." + "\n";
    return fin;
}

std::vector<std::string> parse_helper(std::string str)
{
    int size = str.length();
    std::string a;
    std::vector<std::string> output;
    for (int i = 0; i < size; i++)
    {
        if (str[i] == ';' || str[i] == '.')
        {
            output.push_back(a);
            a = "";
        }
        else
        {
            a += str[i];
        }
    }

    return output;
}

std::vector<std::string> parse_output_from_ros(std::string str)
{
    int size = str.length();
    std::string a;
    std::vector<std::string> output;
    for (int i = 0; i < size; i++)
    {
        if (str[i] == ',' || str[i] == '.')
        {
            output.push_back(a);
            a = "";
        }
        else
        {
            a += str[i];
        }
    }

    return output;
}

Item parse_string_To_Item(std::string item_stringform)
{
    Item tmp;
    std::vector<std::string> items;
    Coordinate x_y_z;

    items = parse_helper(item_stringform);

    tmp.maze_name = items[0];
    tmp.item_name = items[1];

    x_y_z.x = string_to_float(items[2]);
    x_y_z.y = string_to_float(items[3]);

    tmp.location = x_y_z;

    return tmp;
}

bool found_before(std::string item_name)
{
    int size = (int)Robot_RAM.size();
    for (int i = 0; i < size; i++)
    {
        if (Robot_RAM[i].item_name == item_name && Robot_RAM[i].maze_name == maze_name)
        {
            return true;
        }
    }
    return false;
}

std::string change_to_lowercase(std::string str)
{
    int size = str.length();
    std::string a;
    for (int i = 0; i < size; i++)
    {
        a += tolower(str[i]);
    }
    return a;
}

float string_to_float(std::string str)
{
    std::string::size_type sz; // alias of size_t
    float flt = std::stof(str, &sz);
    return flt;
}

std::string float_to_string(float flt)
{
    return std::to_string(flt);
}

std::vector<std::string> parse_input(std::string str)
{
    int size = str.length();
    std::string a;
    std::vector<std::string> output;
    for (int i = 0; i < size; i++)
    {
        if (!isspace(str[i]))
        {
            a += str[i];
        }

        else
        {
            if (a != "")
            {
                output.push_back(a);
                a = "";
            }
        }
    }

    if (a != "")
    {
        output.push_back(a);
        a = "";
    }

    return output;
}
