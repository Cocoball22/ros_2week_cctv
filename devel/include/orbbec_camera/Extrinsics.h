// Generated by gencpp from file orbbec_camera/Extrinsics.msg
// DO NOT EDIT!


#ifndef ORBBEC_CAMERA_MESSAGE_EXTRINSICS_H
#define ORBBEC_CAMERA_MESSAGE_EXTRINSICS_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace orbbec_camera
{
template <class ContainerAllocator>
struct Extrinsics_
{
  typedef Extrinsics_<ContainerAllocator> Type;

  Extrinsics_()
    : header()
    , rotation()
    , translation()  {
      rotation.assign(0.0);

      translation.assign(0.0);
  }
  Extrinsics_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , rotation()
    , translation()  {
  (void)_alloc;
      rotation.assign(0.0);

      translation.assign(0.0);
  }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef boost::array<double, 9>  _rotation_type;
  _rotation_type rotation;

   typedef boost::array<double, 3>  _translation_type;
  _translation_type translation;





  typedef boost::shared_ptr< ::orbbec_camera::Extrinsics_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::orbbec_camera::Extrinsics_<ContainerAllocator> const> ConstPtr;

}; // struct Extrinsics_

typedef ::orbbec_camera::Extrinsics_<std::allocator<void> > Extrinsics;

typedef boost::shared_ptr< ::orbbec_camera::Extrinsics > ExtrinsicsPtr;
typedef boost::shared_ptr< ::orbbec_camera::Extrinsics const> ExtrinsicsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::orbbec_camera::Extrinsics_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::orbbec_camera::Extrinsics_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::orbbec_camera::Extrinsics_<ContainerAllocator1> & lhs, const ::orbbec_camera::Extrinsics_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.rotation == rhs.rotation &&
    lhs.translation == rhs.translation;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::orbbec_camera::Extrinsics_<ContainerAllocator1> & lhs, const ::orbbec_camera::Extrinsics_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace orbbec_camera

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::orbbec_camera::Extrinsics_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::orbbec_camera::Extrinsics_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::orbbec_camera::Extrinsics_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::orbbec_camera::Extrinsics_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::orbbec_camera::Extrinsics_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::orbbec_camera::Extrinsics_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::orbbec_camera::Extrinsics_<ContainerAllocator> >
{
  static const char* value()
  {
    return "3627b43073f4cd5dd6dc179a49eda2ad";
  }

  static const char* value(const ::orbbec_camera::Extrinsics_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x3627b43073f4cd5dULL;
  static const uint64_t static_value2 = 0xd6dc179a49eda2adULL;
};

template<class ContainerAllocator>
struct DataType< ::orbbec_camera::Extrinsics_<ContainerAllocator> >
{
  static const char* value()
  {
    return "orbbec_camera/Extrinsics";
  }

  static const char* value(const ::orbbec_camera::Extrinsics_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::orbbec_camera::Extrinsics_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Header header\n"
"float64[9] rotation\n"
"float64[3] translation\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
;
  }

  static const char* value(const ::orbbec_camera::Extrinsics_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::orbbec_camera::Extrinsics_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.rotation);
      stream.next(m.translation);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Extrinsics_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::orbbec_camera::Extrinsics_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::orbbec_camera::Extrinsics_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "rotation[]" << std::endl;
    for (size_t i = 0; i < v.rotation.size(); ++i)
    {
      s << indent << "  rotation[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.rotation[i]);
    }
    s << indent << "translation[]" << std::endl;
    for (size_t i = 0; i < v.translation.size(); ++i)
    {
      s << indent << "  translation[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.translation[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // ORBBEC_CAMERA_MESSAGE_EXTRINSICS_H
