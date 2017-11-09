# comp150-Robotics
COMP150 robotics project

note : When doing ROS full install, gazebo 7.0 is automatically installed. There is gazebo 8.0, but I decided not to upgrade to it.
# Guide to installing ROS and Gazebo(on Ubuntu VMware)
1. Follow http://wiki.ros.org/kinetic/Installation/Ubuntu. Do desktop full install.
2. In general, doing full install for ROS also installs gazebo. If you want more info on gazebo installation, read this http://gazebosim.org/tutorials?tut=ros_installing&cat=connect_ros.
3. Default gazebo version on ROS is 7.0.0. The latest gazebo version is 8, but we want to use the latest version of 7 just in case 8 breaks. Latest gazebo7 version is 7.8.1. To install gazebo 7.8.1, do the following.
    -   sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
    - cat /etc/apt/sources.list.d/gazebo-stable.list
    - sudo apt-get update
    - sudo apt-get install gazebo7
    - gazebo --version (should return 7.8.1)
4. After that, I had to reboot for unknown reason for gazebo to open.
5. Run this to install turtlebot(or turtlebot3? I haven't tried this one. Not sure what the difference is)
    - sudo apt-get install linux-headers-generic
    - sudo apt-get update
    - sudo apt-get install ros-kinetic-librealsense
    - sudo apt-get install ros-kinetic-turtlebot
    - sudo apt-get install ros-kinetic-turtlebot-gazebo
    - Try "roslaunch turtlebot_gazebo turtlebot_world.launch"

# Starting for the first time
1. Pull this repository.
2. You will see catkin_ws directory inside. Go into the directory.
3. Type "catkin_make". This basically calls build commands via cmake and will build everything on the catkin_ws directory.
4. Source setup.sh inside devel directory. I suggest adding it to bashrc.
5. On bashrc, you should now have two lines, one sourcing /opt/ros/kinetic/setup.bash for ROS, and devel/setup.sh for our workspace directory.
6. Try running "roscore", then on your other terminal "rosrun gazebo_ros gazebo".

# TODO List
- Create simple map using gazebo build editor(Or download one). I think we should create one by our own as example maps are very sophisticated for testing our basic functions.
- Decorate the map with objects and colors.
- Create a robot(we will use turtlebot)
- Get the robot to navigate around the map using keyboard first.
- Integrate computer vision and let the robot navigate around the map and build topological map from it.
- Integrate nodes and edges for pathfinding algorithm.
- Make the robot look for the object around the map and stop when found.
- Robot needs to go back to home base and recalculate the path to the object via pathfinding algorithm.
- Once above is done, do it for multiple objects.
- If all goes well, test it using real robot.

# Current issues
JONG
- I can't get gazebo to run properly on my Mac's vmware running ubuntu. I am working with my desktop now. One way I found to run gazebo on ubuntu vmware is by adding this to the line
    "export export SVGA_VGPU10=0"
- Only when I updated gazebo to 7.8.1, the willow garage world and other stuffs started working.
- According to readings, gazebo sometimes runs into segmentation fault because there is no nvidia graphics card. In that case, just keep launching until it works.
