/**
 * @file target_reacher.cpp
 * @author Aaqib Barodawala
 * @author Ankur Chavan
 * @author Krishna Hundekari
 * @brief Implementation of the target_reacher to reach the final destination,
 * @version 0.1
 * @date 2022-12-16
 *
 */

#include <rclcpp/rclcpp.hpp>
#include "target_reacher/target_reacher.h"


// Broadcasting final_destination frame 
void TargetReacher::final_destination(int a)
{
        geometry_msgs::msg::TransformStamped f;

        f.header.stamp = this->get_clock()->now();
        f.header.frame_id = fd_frame_id;
        f.child_frame_id = "final_destination";

        if (a==0)
        {
            f.transform.translation.x = fd_aruco0_x;
            f.transform.translation.y = fd_aruco0_y;
            f.transform.translation.z = 0.0;
        }else if (a==1)
        {
            f.transform.translation.x = fd_aruco1_x;
            f.transform.translation.y = fd_aruco1_y;
            f.transform.translation.z = 0.0;
        }else if (a==2)
        {
            f.transform.translation.x = fd_aruco2_x;
            f.transform.translation.y = fd_aruco2_y;
            f.transform.translation.z = 0.0;
        }else if (a==3)
        {
            f.transform.translation.x = fd_aruco3_x;
            f.transform.translation.y = fd_aruco3_y;
            f.transform.translation.z = 0.0;
        } 

        f.transform.rotation.x = 0.0;
        f.transform.rotation.y = 0.0;
        f.transform.rotation.z = 0.0;
        f.transform.rotation.w = 1.0;

        broadcaster->sendTransform(f);

        i=true;
}


// Checking the aruco marker and deciding the final destination
void TargetReacher::cb1(const std::shared_ptr<ros2_aruco_interfaces::msg::ArucoMarkers> aruco)
{
    auto x = aruco->marker_ids;
    if (x.at(0)==0){
        auto a=0;
        final_destination(a);
    }else if (x.at(0)==1){
        auto a=1;
        final_destination(a);
    }else if (x.at(0)==2){
        auto a=2;
        final_destination(a);
    }else if (x.at(0)==3){
        auto a=3;
        final_destination(a);
    }
}

// Rotating the turtlebot when it reaches goal number 1
void TargetReacher::timer_callback(const std::shared_ptr<std_msgs::msg::Bool> msg)
{
    if (msg->data)
    {
        geometry_msgs::msg::Twist vel;
        if (goal_reached)
        {
            vel.linear.x = 0;
            vel.angular.z = 0.2;    
        } 
        else
        {
            vel.linear.x = 0;
            vel.angular.z = 0;   
        }
        m_publisher_cmd_vel->publish(vel);
        goal_reached = false;
        ros2_aruco_interfaces::msg::ArucoMarkers aruco;

    }
}

// Transform Listener 
void TargetReacher::cb2()
{
    if (i==true)
    {
        geometry_msgs::msg::TransformStamped t;
        // Look up for the transformation between "robot1/odom" and "final_destination" frames
        try
        {
            t = m_tf_buffer->lookupTransform("robot1/odom", "final_destination", tf2::TimePointZero);
        }
        catch (const tf2::TransformException &ex)
        {
            RCLCPP_INFO(
                this->get_logger(), "Could not transform %s to %s: %s",
                "robot1/odom", "final_destination", ex.what());
            return;
        }

        RCLCPP_INFO(
            this->get_logger(), "Moving to goal [%f, %f]", t.transform.translation.x, t.transform.translation.y);

        m_bot_controller->set_goal(t.transform.translation.x, t.transform.translation.y);
    }
}