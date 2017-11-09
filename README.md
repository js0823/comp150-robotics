# comp150-Robotics
COMP150 robotics project

note : When doing ROS full install, gazebo 7.0 is automatically installed. There is gazebo 8.0, but I decided not to upgrade to it.
# Guide to installing ROS and Gazebo(on Ubuntu VMware)
1. Follow http://wiki.ros.org/kinetic/Installation/Ubuntu. Do desktop full install.
2. For gazebo, I followed http://gazebosim.org/tutorials?tut=ros_installing&cat=connect_ros.

# Starting for the first time
1. Pull this repository.
2. You will see catkin_ws directory inside. Go into the directory.
3. Type "catkin_make". This basically calls build commands via cmake and will build everything on the catkin_ws directory.
4. Source setup.sh inside devel directory. I suggest adding it to bashrc.
5. On bashrc, you should now have two lines, one sourcing /opt/ros/kinetic/setup.bash for ROS, and devel/setup.sh for our workspace directory.
6. Install gazebo_src_pkgs by following http://gazebosim.org/tutorials?tut=ros_installing&cat=connect_ros. This will allow integration with ROS(I think).

- I can't get gazebo to run properly on my Mac's vmware running ubuntu. I am working with my desktop now.
- To get the maps, you need to build gazebo by doing the following commands.
    1. sudo apt-get install -y libgazebo7-dev
    2. cd [git-repo]/catkin_ws/src
    3. git clone https://github.com/ros-simulation/gazebo_ros_pkgs.git -b kinetic-devel
    4. rosdep update
    5. rosdep check --from-paths . --ignore-src --rosdistro kinetic
    6. cd [git-repo]/catkin_ws/
    7. catkin_make
    8. This builds gazebo, and has some worlds that is already built in. Willowgarage world looks good.
