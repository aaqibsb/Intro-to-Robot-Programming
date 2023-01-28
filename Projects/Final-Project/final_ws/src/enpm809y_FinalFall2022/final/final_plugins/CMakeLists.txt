cmake_minimum_required(VERSION 3.8)
project(final_plugins)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(gazebo_msgs REQUIRED)
find_package(gazebo_ros REQUIRED)
find_package(rclcpp REQUIRED)

link_directories(${gazebo_dev_LIBRARY_DIRS})


include_directories(include/final_plugins)

# Disable Shadows Plugin
add_library(disable_shadows_plugin SHARED
  src/disable_shadows_plugin.cpp
)
target_include_directories(disable_shadows_plugin PUBLIC include)
ament_target_dependencies(disable_shadows_plugin
  "gazebo_ros"
)
ament_export_libraries(disable_shadows_plugin)

ament_package()

install(DIRECTORY include/final_plugins/
        DESTINATION include)

install(TARGETS
    disable_shadows_plugin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin)

# install(DIRECTORY models
#   DESTINATION share/${PROJECT_NAME}/
# )