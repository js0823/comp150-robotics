#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/jyoon10/gitrepo/comp150-robotics/catkin_ws/src/gazebo_ros_pkgs/gazebo_ros"

# snsure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/jyoon10/gitrepo/comp150-robotics/catkin_ws/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/jyoon10/gitrepo/comp150-robotics/catkin_ws/install/lib/python2.7/dist-packages:/home/jyoon10/gitrepo/comp150-robotics/catkin_ws/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/jyoon10/gitrepo/comp150-robotics/catkin_ws/build" \
    "/usr/bin/python" \
    "/home/jyoon10/gitrepo/comp150-robotics/catkin_ws/src/gazebo_ros_pkgs/gazebo_ros/setup.py" \
    build --build-base "/home/jyoon10/gitrepo/comp150-robotics/catkin_ws/build/gazebo_ros_pkgs/gazebo_ros" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/jyoon10/gitrepo/comp150-robotics/catkin_ws/install" --install-scripts="/home/jyoon10/gitrepo/comp150-robotics/catkin_ws/install/bin"
