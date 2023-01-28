// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ros2_aruco_interfaces:msg/ArucoMarkers.idl
// generated code does not contain a copyright notice

#ifndef ROS2_ARUCO_INTERFACES__MSG__DETAIL__ARUCO_MARKERS__STRUCT_HPP_
#define ROS2_ARUCO_INTERFACES__MSG__DETAIL__ARUCO_MARKERS__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'poses'
#include "geometry_msgs/msg/detail/pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__ros2_aruco_interfaces__msg__ArucoMarkers __attribute__((deprecated))
#else
# define DEPRECATED__ros2_aruco_interfaces__msg__ArucoMarkers __declspec(deprecated)
#endif

namespace ros2_aruco_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ArucoMarkers_
{
  using Type = ArucoMarkers_<ContainerAllocator>;

  explicit ArucoMarkers_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit ArucoMarkers_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _marker_ids_type =
    std::vector<int64_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int64_t>>;
  _marker_ids_type marker_ids;
  using _poses_type =
    std::vector<geometry_msgs::msg::Pose_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Pose_<ContainerAllocator>>>;
  _poses_type poses;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__marker_ids(
    const std::vector<int64_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int64_t>> & _arg)
  {
    this->marker_ids = _arg;
    return *this;
  }
  Type & set__poses(
    const std::vector<geometry_msgs::msg::Pose_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<geometry_msgs::msg::Pose_<ContainerAllocator>>> & _arg)
  {
    this->poses = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ros2_aruco_interfaces::msg::ArucoMarkers_<ContainerAllocator> *;
  using ConstRawPtr =
    const ros2_aruco_interfaces::msg::ArucoMarkers_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ros2_aruco_interfaces::msg::ArucoMarkers_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ros2_aruco_interfaces::msg::ArucoMarkers_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ros2_aruco_interfaces::msg::ArucoMarkers_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ros2_aruco_interfaces::msg::ArucoMarkers_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ros2_aruco_interfaces::msg::ArucoMarkers_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ros2_aruco_interfaces::msg::ArucoMarkers_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ros2_aruco_interfaces::msg::ArucoMarkers_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ros2_aruco_interfaces::msg::ArucoMarkers_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ros2_aruco_interfaces__msg__ArucoMarkers
    std::shared_ptr<ros2_aruco_interfaces::msg::ArucoMarkers_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ros2_aruco_interfaces__msg__ArucoMarkers
    std::shared_ptr<ros2_aruco_interfaces::msg::ArucoMarkers_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArucoMarkers_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->marker_ids != other.marker_ids) {
      return false;
    }
    if (this->poses != other.poses) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArucoMarkers_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArucoMarkers_

// alias to use template instance with default allocator
using ArucoMarkers =
  ros2_aruco_interfaces::msg::ArucoMarkers_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace ros2_aruco_interfaces

#endif  // ROS2_ARUCO_INTERFACES__MSG__DETAIL__ARUCO_MARKERS__STRUCT_HPP_
