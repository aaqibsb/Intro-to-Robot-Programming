cmake_minimum_required(VERSION 3.8)
project(world_odom_broadcaster)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rclpy REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)

include_directories(include/world_odom_broadcaster)


add_executable(world_odom_broadcaster src/world_odom_broadcaster.cpp src/main.cpp)
ament_target_dependencies(world_odom_broadcaster rclcpp geometry_msgs tf2_ros)

install(TARGETS 
world_odom_broadcaster
DESTINATION lib/${PROJECT_NAME})

ament_package()
