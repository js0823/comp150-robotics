# comp150-Robotics
COMP150 robotics project

note : When doing ROS full install, gazebo 7.0 is automatically installed. There is gazebo 8.0, but I decided not to upgrade to it.
# Guide to installing ROS and Gazebo(on Ubuntu VMware)
1. Follow http://wiki.ros.org/kinetic/Installation/Ubuntu. Do desktop full install.
2. In general, doing full install for ROS also installs gazebo. If you want more info on gazebo installation, read this http://gazebosim.org/tutorials?tut=ros_installing&cat=connect_ros.

# Starting for the first time
1. Pull this repository.
2. You will see catkin_ws directory inside. Go into the directory.
3. Type "catkin_make". This basically calls build commands via cmake and will build everything on the catkin_ws directory.
4. Source setup.sh inside devel directory. I suggest adding it to bashrc.
5. On bashrc, you should now have two lines, one sourcing /opt/ros/kinetic/setup.bash for ROS, and devel/setup.sh for our workspace directory.
6. Try running "roscore", then on your other terminal "rosrun gazebo_ros gazebo". If this doesn't work. let me know. One problem

# TODO List
- Learn how to use ROS and gazebo.
- Create simple map using gazebo build editor(Or download one). I think we should create one by our own as example maps are very sophisticated for testing our basic functions.
- Decorate the map with objects and colors.
- Create a robot(or download one. Baxter? More info here http://wiki.ros.org/gazebo_ros_pkgs#Gazebo.2BAC8-ROS_robot_simulations_ready_to_use)
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
