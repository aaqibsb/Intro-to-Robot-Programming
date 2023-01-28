/**
 * @file odom_updater.cpp
 * @author Aaqib Barodawala
 * @author Ankur Chavan
 * @author Krishna Hundekari
 * @brief Implementation of the odom_updater to connect the frame /robot1/base_footprint as a child to frame -/robot1/odom
 * @version 0.1
 * @date 2022-11-07
 *
 */

#include <rclcpp/rclcpp.hpp>
#include "odom_updater/odom_updater.h"

void FramePublisher::timer_callback(const std::shared_ptr<nav_msgs::msg::Odometry> msg)
{
    geometry_msgs::msg::TransformStamped t;

    // Read message content and assign it to
    // corresponding tf variables
    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = "/robot1/odom";
    t.child_frame_id = "/robot1/base_footprint";
    
    // Transform the position and orientation 

    t.transform.translation.x = msg->pose.pose.position.x;
    t.transform.translation.y = msg->pose.pose.position.y;
    t.transform.translation.z = 0.0;

    t.transform.rotation.x = msg->pose.pose.orientation.x;
    t.transform.rotation.y = msg->pose.pose.orientation.y;
    t.transform.rotation.z = msg->pose.pose.orientation.z;
    t.transform.rotation.w = msg->pose.pose.orientation.w;

    // Send the transformation
    tf_broadcaster->sendTransform(t);
  }
