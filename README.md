# comp150-Robotics
COMP150 robotics project

note : When doing ROS full install, gazebo 7.0 is automatically installed. There is gazebo 8.0, but I decided not to upgrade to it.
# Guide to installing ROS and Gazebo(on Ubuntu VMware)
1. Follow http://wiki.ros.org/kinetic/Installation/Ubuntu. Do desktop full install.
2. In general, doing full install for ROS also installs gazebo. If you want more info on gazebo installation, read this http://gazebosim.org/tutorials?tut=ros_installing&cat=connect_ros.
3. Default gazebo version on ROS is 7.0.0. The latest gazebo version is 8, but we want to use the latest version of 7 just in case 8 breaks. Latest gazebo7 version is 7.8.1. To install gazebo 7.8.1, do the following.
    - sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
    - wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
    - sudo apt-get update
    - sudo apt-get install gazebo7
    - gazebo --version (should return 7.8.1)
4. After that, I had to reboot for unknown reason for gazebo to open.
5. Run this to install turtlebot(or turtlebot3? I haven't tried this one. Not sure what the difference is)
    - sudo apt-get update
    - sudo apt-get install linux-headers-generic
    - sudo apt-get install ros-kinetic-turtlebot*
    - sudo apt-get install ros-kinetic-turtlebot-gazebo
    - Try "roslaunch turtlebot_gazebo turtlebot_world.launch"

# Starting for the first time
1. Pull this repository.
2. You will see catkin_ws directory inside. Go into the directory.
3. Type "catkin_make". This basically calls build commands via cmake and will build everything on the catkin_ws directory.
4. Source setup.sh inside devel directory. I suggest adding it to bashrc.
5. On bashrc, you should now have two lines, one sourcing /opt/ros/kinetic/setup.bash for ROS, and devel/setup.sh for our workspace directory.
6. Try running "roscore", then on your other terminal "rosrun gazebo_ros gazebo".
7. set "export TURTLEBOT_3D_SENSOR=kinect". Put this into your bashrc.

# Some Good To Know Commands
- rostopic list
    - Shows all topics currently running on roscore. This is useful when you want to get the output of another package and work on it, such a from turtlebot to your code.
- rosnode list
    - Shows all nodes currently running on roscore. If you run this while running your package, your package should show up here.
- catkin_make
    - Compile all packages. Run this command on catkin_ws directory, and you will see everything gets built in it.

# TODO List
## Creating a world
- We can create a world using gazebo build editor from the gazebo GUI.
- Decorate the map with objects and colors for the turtlebot to see.
- I created a world and saved it to Pathify directory. It's a simple map containing just walls. It would be nice to decorate it, and we need some colors and objects in it.

## Using turtlebot to navigate and build a map of the world
- Getting the robot to navigate around the map using keyboard.
    - terminal 1 = 'roslaunch turtlebot_gazebo turtlebot_world.launch' or 'roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=worlds/willowgarage.world'     
    - terminal 2 = 'roslaunch turtlebot_teleop keyboard_teleop.launch'
    - terminal 3 = 'roslaunch turtlebot_rviz_launchers view_robot.launch' to see what turtlebot sees or
    - terminal 3 = 'roslaunch turtlebot_rviz_launchers view_navigation.launch' to see map building.
- Integrate computer vision and let the robot navigate around the map and build topological map from it.
    - terminal 4 = 'roslaunch turtlebot_gazebo gmapping_demo.launch' to use gmapping to build the map.

## Integrating node and edges in order to calculate shortest path
- We can use frontier exploration to build map autonomously, but we will also need to edit this package in order to create nodes and edges while exploring autonomously.
- We will be using A* algorithm.
- Turtlebot Initial Pose in map1.world : x = -8.982751, y = -2.989552, z = 0.000817, roll = -0.000182, pitch = -0.020424, yaw = -0.000394 

## Using computer vision to find the object
- Make the robot look for the object around the map and stop when found.
- Robot needs to go back to home base and recalculate the path to the object via pathfinding algorithm.
- Once above is done, do it for multiple objects.
- If all goes well, test it using real robot.
- OpenCV install guide - http://www.codebind.com/cpp-tutorial/install-opencv-ubuntu-cpp/
    - Try to install using everything just in case. For example, tbb, qt, jpeg, tiff, png, examples, opengl, python3, etc.
    - I installed on /opt/opencv/3.3.1 and set "export opencv3_DIR=/opt/opencv/3.3.1
- ImageDetector.cpp is the openCV which will be the front camera as well as image detection.
    - To use it, do
        - Make sure the code is compiled.
        - Type "export ROBOT_INITIAL_POSE="-x -8.982751 -y -2.989552 -z 0" "
        - In another terminal, type "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/jyoon10/git-repo/comp150-robotics/catkin_ws/src/pathify/pathifyMaps/map1.world" (roslaunch launches roscore automatically if roscore is not found running)
        - In another terminal, type "roslaunch turtlebot_teleop keyboard_teleop.launch"
        - In another terminal, type "rosrun pathify image_detector"
- Grey wall on gazebo RGB value is 116,116,116
- Red wall RGB = 203~204, 105, 105
- Blue wall RGB = 
- Yellow wall RGB = 

## Issuing commands to turtlebot
- By issuing command either by command line or speech recognition, turtlebot will need to do everything above.

# Good tutorials
- Turtlebot and gazebo tutorial http://learn.turtlebot.com/2015/02/03/1/
- Frontier exploration http://wiki.ros.org/frontier_exploration
- Gmapping http://wiki.ros.org/turtlebot_gazebo/Tutorials/indigo/Make%20a%20map%20and%20navigate%20with%20it
- SLAM map building http://wiki.ros.org/turtlebot_navigation/Tutorials/indigo/Build%20a%20map%20with%20SLAM
- Another building map tutorial http://wiki.ros.org/turtlebot_simulator/Tutorials/fuerte/Building%20a%20Map%20in%20TurtleBot%20Simulator

# Current issues
JONG
- I can't get gazebo to run properly on my Mac's vmware running ubuntu. I am working with my desktop now. One way I found to run gazebo on ubuntu vmware is by adding this to the line
    "export export SVGA_VGPU10=0"
- Only when I updated gazebo to 7.8.1, the willow garage world and other stuffs started working.
- According to readings, gazebo sometimes runs into segmentation fault because there is no nvidia graphics card. In that case, just keep launching until it works.
