# Pathify
COMP150 robotics project

# Prerequisite before Running the project(on Ubuntu)
1. Follow http://wiki.ros.org/kinetic/Installation/Ubuntu. Do desktop full install.
2. Default gazebo version on ROS Kinetic is 7.0.0. The latest gazebo version is 8, but we want to use the latest version of 7 just in case 8 breaks. Latest gazebo7 version is 7.8.1. To install gazebo 7.8.1, do the following.
    - sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
    - wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add -
    - sudo apt-get update
    - sudo apt-get install gazebo7
    - gazebo --version (should return 7.8.1)
3. Run this to install turtlebot
    - sudo apt-get update
    - sudo apt-get install linux-headers-generic
    - sudo apt-get install ros-kinetic-turtlebot*
    - sudo apt-get install ros-kinetic-turtlebot-gazebo
    - Try "roslaunch turtlebot_gazebo turtlebot_world.launch". This command should open gazebo with the turtlebot and the world.
4. Type "source /opt/ros/kinetic/setup.bash" on your terminal. Alternatively, you can add the command to your bashrc.
5. Now you should be all set to start running this project!

# Guide to building the project
1. Pull this repository to your desired location.
2. You will see catkin_ws directory inside. Go into the directory.
3. Type "catkin_make" on the catkin_ws directory to build the Pathify package.
4. Source setup.bash inside devel directory. I suggest adding it to bashrc.
5. On bashrc, you should now have two lines, one sourcing /opt/ros/kinetic/setup.bash for ROS, and devel/setup.sh for our workspace directory.
7. set "export TURTLEBOT_3D_SENSOR=kinect". I recommend putting this into your bashrc if you will always use kinect for Turtlebot simulation.


# Guide to running the project
1. Run command "roslaunch pathify pathify_turtlebot_gazebo_world3.launch".
    - There are total of three launch files for opening our customized maps. I suggest using world3 as that is our latest customized map.
2. Run command "roslaunch pathify pathify_nav.launch" on another terminal.
3. Run command "rosrun robot_pose_publisher robot_pose_publisher" on another terminal.
4. Run command "roslaunch pathify pathify_imageDetector.launch" on another terminal.
5. Finally, run command "roslaunch pathify pathify_inputTalker.launch" on another terminal.

# User Guide
The command prompt I/O interface from pathify_inputTalker.launch is simple and straight forward.
Once the turtlebot has localized its estimated position on the map, it will first ask for map name.
Type the map name of your choice(it can be anything but because the saved position text file uses map name for storage, I suggest using a simple name).
Rest is following the example on the command prompt.