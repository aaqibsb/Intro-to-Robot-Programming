#include <string>
#include "world_odom_broadcaster.h"
#include "tf2/LinearMath/Quaternion.h"
#include "geometry_msgs/msg/pose.hpp"
#include "rclcpp/rclcpp.hpp"

void WorldOdomBroadcaster::timer_callback()
{
    broadcast_world_odom();
}

void WorldOdomBroadcaster::broadcast_world_odom()
{
    geometry_msgs::msg::TransformStamped t;

    std::string odom = "/robot1/odom";
    std::string origin1 = "origin1";
    std::string origin2 = "origin2";
    std::string origin3 = "origin3";
    std::string origin4 = "origin4";

    /*******************************************
     * static broadcaster: "world" -> "/robot1/odom"
     *******************************************/
    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = "world";
    t.child_frame_id = odom;

    t.transform.translation.x = 0;
    t.transform.translation.y = 0;
    t.transform.translation.z = 0;

    tf2::Quaternion q;
    q.setRPY(0, 0, 0);
    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    // Send the transformation
    m_tf_broadcaster->sendTransform(t);

    /*******************************************
     * static broadcaster: "world" -> "origin1"
     *******************************************/
    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = "world";
    t.child_frame_id = origin1;

    t.transform.translation.x = 2;
    t.transform.translation.y = 2;
    t.transform.translation.z = 0;

    // tf2::Quaternion q;
    q.setRPY(0, 0, 1.57);
    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    // Send the transformation
    m_tf_broadcaster->sendTransform(t);

    /*******************************************
     * static broadcaster: "world" -> "origin2"
     *******************************************/
    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = "world";
    t.child_frame_id = origin2;

    t.transform.translation.x = -2;
    t.transform.translation.y = -2;
    t.transform.translation.z = 0;

    // tf2::Quaternion q;
    q.setRPY(0, 0, 1.57);
    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    // Send the transformation
    m_tf_broadcaster->sendTransform(t);

    /*******************************************
     * static broadcaster: "world" -> "origin3"
     *******************************************/
    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = "world";
    t.child_frame_id = origin3;

    t.transform.translation.x = -2;
    t.transform.translation.y = 2;
    t.transform.translation.z = 0;

    // tf2::Quaternion q;
    q.setRPY(0, 0, 1.57);
    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    // Send the transformation
    m_tf_broadcaster->sendTransform(t);

    /*******************************************
     * static broadcaster: "world" -> "origin4"
     *******************************************/
    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = "world";
    t.child_frame_id = origin4;

    t.transform.translation.x = 2;
    t.transform.translation.y = -2;
    t.transform.translation.z = 0;

    // tf2::Quaternion q;
    q.setRPY(0, 0, 1.57);
    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    // Send the transformation
    m_tf_broadcaster->sendTransform(t);
}

