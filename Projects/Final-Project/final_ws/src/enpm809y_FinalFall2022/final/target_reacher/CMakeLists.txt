cmake_minimum_required(VERSION 3.8)
project(target_reacher)

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
find_package(geometry_msgs REQUIRED)
find_package(bot_controller REQUIRED)
find_package(ros2_aruco_interfaces REQUIRED)
find_package(tf2_ros REQUIRED)


include_directories(include)


add_executable(target_reacher src/target_reacher.cpp src/main.cpp)
ament_target_dependencies(target_reacher bot_controller tf2_ros ros2_aruco_interfaces rclcpp geometry_msgs)


#############
## Install ##
#############
install(DIRECTORY include/${PROJECT_NAME} DESTINATION include)
install(DIRECTORY params DESTINATION share/${PROJECT_NAME})
install(TARGETS target_reacher DESTINATION lib/${PROJECT_NAME}/)

ament_package()
