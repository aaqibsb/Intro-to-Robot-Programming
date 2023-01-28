// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ros2_aruco_interfaces:msg/ArucoMarkers.idl
// generated code does not contain a copyright notice

#ifndef ROS2_ARUCO_INTERFACES__MSG__DETAIL__ARUCO_MARKERS__TRAITS_HPP_
#define ROS2_ARUCO_INTERFACES__MSG__DETAIL__ARUCO_MARKERS__TRAITS_HPP_

#include "ros2_aruco_interfaces/msg/detail/aruco_markers__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'poses'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const ros2_aruco_interfaces::msg::ArucoMarkers & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_yaml(msg.header, out, indentation + 2);
  }

  // member: marker_ids
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.marker_ids.size() == 0) {
      out << "marker_ids: []\n";
    } else {
      out << "marker_ids:\n";
      for (auto item : msg.marker_ids) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: poses
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.poses.size() == 0) {
      out << "poses: []\n";
    } else {
      out << "poses:\n";
      for (auto item : msg.poses) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ros2_aruco_interfaces::msg::ArucoMarkers & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<ros2_aruco_interfaces::msg::ArucoMarkers>()
{
  return "ros2_aruco_interfaces::msg::ArucoMarkers";
}

template<>
inline const char * name<ros2_aruco_interfaces::msg::ArucoMarkers>()
{
  return "ros2_aruco_interfaces/msg/ArucoMarkers";
}

template<>
struct has_fixed_size<ros2_aruco_interfaces::msg::ArucoMarkers>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ros2_aruco_interfaces::msg::ArucoMarkers>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ros2_aruco_interfaces::msg::ArucoMarkers>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROS2_ARUCO_INTERFACES__MSG__DETAIL__ARUCO_MARKERS__TRAITS_HPP_
