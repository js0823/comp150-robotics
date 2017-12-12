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
- Turtlebot Initial Pose in map1.world : x = -8.982751, y = -2.989552, z = 0, roll = -0.000182, pitch = -0.020424, yaw = -0.000394
- Turtlebot Initial Pose in map2.world : x = -0.298748, y = -4.087023, z = 0, roll = 0.000766, pitch = -0.014433, yaw = -0.014433

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
        - In another terminal, type "roslaunch pathify pathify.launch"
- Grey wall on gazebo RGB value is 116,116,116 (so ignore any color close to the value)
- Red wall RGB = 203~204, 105, 105
- Blue wall RGB = 
- Yellow wall RGB = 
- Check difference between pathify.rviz and /opt/ros/kinetic/share/turtlebot_rviz_launchers/rviz/robot.rviz

## Issuing commands to turtlebot
- By issuing command either by command line or speech recognition, turtlebot will need to do everything above.

# Current Starting Guide (To run the project)