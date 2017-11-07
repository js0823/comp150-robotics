// Generated by gencpp from file gazebo_msgs/SetLinkPropertiesResponse.msg
// DO NOT EDIT!


#ifndef GAZEBO_MSGS_MESSAGE_SETLINKPROPERTIESRESPONSE_H
#define GAZEBO_MSGS_MESSAGE_SETLINKPROPERTIESRESPONSE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace gazebo_msgs
{
template <class ContainerAllocator>
struct SetLinkPropertiesResponse_
{
  typedef SetLinkPropertiesResponse_<ContainerAllocator> Type;

  SetLinkPropertiesResponse_()
    : success(false)
    , status_message()  {
    }
  SetLinkPropertiesResponse_(const ContainerAllocator& _alloc)
    : success(false)
    , status_message(_alloc)  {
  (void)_alloc;
    }



   typedef uint8_t _success_type;
  _success_type success;

   typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _status_message_type;
  _status_message_type status_message;




  typedef boost::shared_ptr< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> const> ConstPtr;

}; // struct SetLinkPropertiesResponse_

typedef ::gazebo_msgs::SetLinkPropertiesResponse_<std::allocator<void> > SetLinkPropertiesResponse;

typedef boost::shared_ptr< ::gazebo_msgs::SetLinkPropertiesResponse > SetLinkPropertiesResponsePtr;
typedef boost::shared_ptr< ::gazebo_msgs::SetLinkPropertiesResponse const> SetLinkPropertiesResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace gazebo_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': False}
// {'sensor_msgs': ['/opt/ros/kinetic/share/sensor_msgs/cmake/../msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'trajectory_msgs': ['/opt/ros/kinetic/share/trajectory_msgs/cmake/../msg'], 'gazebo_msgs': ['/home/jyoon10/gitrepo/comp150-robotics/catkin_ws/src/gazebo_ros_pkgs/gazebo_msgs/msg'], 'geometry_msgs': ['/opt/ros/kinetic/share/geometry_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "2ec6f3eff0161f4257b808b12bc830c2";
  }

  static const char* value(const ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x2ec6f3eff0161f42ULL;
  static const uint64_t static_value2 = 0x57b808b12bc830c2ULL;
};

template<class ContainerAllocator>
struct DataType< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "gazebo_msgs/SetLinkPropertiesResponse";
  }

  static const char* value(const ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bool success\n\
string status_message\n\
\n\
";
  }

  static const char* value(const ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.success);
      stream.next(m.status_message);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetLinkPropertiesResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::gazebo_msgs::SetLinkPropertiesResponse_<ContainerAllocator>& v)
  {
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
    s << indent << "status_message: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.status_message);
  }
};

} // namespace message_operations
} // namespace ros

#endif // GAZEBO_MSGS_MESSAGE_SETLINKPROPERTIESRESPONSE_H
