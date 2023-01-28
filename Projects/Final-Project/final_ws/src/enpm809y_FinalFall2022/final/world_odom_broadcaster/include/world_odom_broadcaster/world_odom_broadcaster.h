#pragma once

#include "rclcpp/rclcpp.hpp"
#include <nav_msgs/msg/odometry.hpp>
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/pose.hpp"
#include "tf2_ros/static_transform_broadcaster.h"
#include <string>

class WorldOdomBroadcaster : public rclcpp::Node
{
public:
    WorldOdomBroadcaster(std::string node_name) : Node(node_name)
    {
        // Initialize the transform broadcaster
        m_tf_broadcaster =
            std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);

        // Create a timer
        m_timer = this->create_wall_timer(std::chrono::milliseconds((int)(1000.0 / 1.0)),
                                          std::bind(&WorldOdomBroadcaster::timer_callback, this));
    }

private:
    // attributes
    rclcpp::TimerBase::SharedPtr m_timer;
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> m_tf_broadcaster;

    // methods
    void broadcast_world_odom();
    void timer_callback();
};