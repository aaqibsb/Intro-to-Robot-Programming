/**
 * @file target_reacher.h
 * @author Aaqib Barodawala
 * @author Ankur Chavan
 * @author Krishna Hundekari
 * @brief Defining the target_reacher
 * @version 0.1
 * @date 2022-12-16
 *
 */

#pragma once
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <string>
#include "bot_controller/bot_controller.h"
#include "ros2_aruco_interfaces/msg/aruco_markers.hpp"
#include "tf2_ros/static_transform_broadcaster.h"
#include "tf2_ros/transform_broadcaster.h"

using namespace std::chrono_literals;

/**
 * @brief ROS2 node for reaching a target location using odometry data and aruco markers.
 * 
 * This node subscribes to the "/aruco_markers" and "/goal_reached" topics, and publishes
 * geometry_msgs::msg::Twist messages to the "/robot1/cmd_vel" topic. It uses the data from the
 * "/aruco_markers" topic to determine the final destination origin from final_params.yaml file, and the
 * geometry_msgs::msg::Twist messages to control the robot's movement. The node also broadcasts the
 * final destination of the robot as a static transform.
 */

class TargetReacher : public rclcpp::Node
{
public:

    /**
     * @brief Constructs a new TargetReacher object.
     * 
     * Initializes the node and sets up subscriptions to the "/aruco_markers" and "/goal_reached"
     * topics, as well as a publisher for the "/robot1/cmd_vel" topic. It also reads in various
     * parameters from the parameter server, including the target location, the final destination, and
     * the frame IDs for the various transforms. A wall timer is set up to call the cb2 function
     * every second.
     * 
     * @param bot_controller Shared pointer to a BotController object for controlling the robot's movement.
     */

    TargetReacher(std::shared_ptr<BotController> const &bot_controller) : Node("target_reacher")
    {

        m_bot_controller = bot_controller;

        // First goal x-coordinate

        auto aruco_target_x = this->declare_parameter<double>("aruco_target.x");

        // First goal y-coordinate

        auto aruco_target_y = this->declare_parameter<double>("aruco_target.y");

        // final destination frame id/origin

        fd_frame_id = this->declare_parameter<std::string>("final_destination.frame_id");

        fd_aruco0_x = this->declare_parameter<double>("final_destination.aruco_0.x");
        fd_aruco0_y = this->declare_parameter<double>("final_destination.aruco_0.y");

        fd_aruco1_x = this->declare_parameter<double>("final_destination.aruco_1.x");
        fd_aruco1_y = this->declare_parameter<double>("final_destination.aruco_1.y");

        fd_aruco2_x = this->declare_parameter<double>("final_destination.aruco_2.x");
        fd_aruco2_y = this->declare_parameter<double>("final_destination.aruco_2.y");

        fd_aruco3_x = this->declare_parameter<double>("final_destination.aruco_3.x");
        fd_aruco3_y = this->declare_parameter<double>("final_destination.aruco_3.y");

        m_bot_controller->set_goal(aruco_target_x, aruco_target_y);
        
        //publish velocity
        m_publisher_cmd_vel = this->create_publisher<geometry_msgs::msg::Twist>("/robot1/cmd_vel", 10);

        //publish boolean value for goal
        m_subscriber_goal = this->create_subscription<std_msgs::msg::Bool>("/goal_reached", 10, std::bind(&TargetReacher::timer_callback, this, std::placeholders::_1));

        //subscribe aruco markers 
        m_subscriber_aruco = this->create_subscription<ros2_aruco_interfaces::msg::ArucoMarkers>("/aruco_markers", 10, std::bind(&TargetReacher::cb1, this, std::placeholders::_1));
        
        //broadcaster for final destination
        broadcaster = std::make_unique<tf2_ros::StaticTransformBroadcaster>(this);

        //transform listener
        m_tf_buffer = std::make_unique<tf2_ros::Buffer>(this->get_clock());
        m_tf_listener = std::make_shared<tf2_ros::TransformListener>(*m_tf_buffer);

        // Call on_timer function every second (Transform Listener)
        m_timer = this->create_wall_timer(1s, std::bind(&TargetReacher::cb2, this));
    }

private:

    // attributes
    std::shared_ptr<BotController> m_bot_controller;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr m_subscriber_goal;
    rclcpp::Subscription<ros2_aruco_interfaces::msg::ArucoMarkers>::SharedPtr m_subscriber_aruco;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr m_publisher_cmd_vel;
    std::unique_ptr<tf2_ros::StaticTransformBroadcaster> broadcaster;

    rclcpp::TimerBase::SharedPtr m_timer{nullptr};
    std::shared_ptr<tf2_ros::TransformListener> m_tf_listener{nullptr};
    std::unique_ptr<tf2_ros::Buffer> m_tf_buffer;

    bool i=false;

    bool goal_reached=true;

    /**
     * @brief Final destination frame id
     * 
     */

    std::string fd_frame_id;
    
    /**
     * @brief X-coordinate of final destination when frame id is 0
     * 
     */

    double fd_aruco0_x;

    /**
     * @brief Y-coordinate of final destination when frame id is 0
     * 
     */

    double fd_aruco0_y;

    /**
     * @brief X-coordinate of final destination when frame id is 1
     * 
     */

    double fd_aruco1_x;

    /**
     * @brief Y-coordinate of final destination when frame id is 1
     * 
     */

    double fd_aruco1_y;

    /**
     * @brief X-coordinate of final destination when frame id is 2
     * 
     */

    double fd_aruco2_x;

    /**
     * @brief Y-coordinate of final destination when frame id is 2
     * 
     */

    double fd_aruco2_y;

    /**
     * @brief X-coordinate of final destination when frame id is 3
     * 
     */

    double fd_aruco3_x;

    /**
     * @brief Y-coordinate of final destination when frame id is 3
     * 
     */

    double fd_aruco3_y;

    /**
     * @brief Broadcaster for TargetReacher
     * 
     * @param i takes integer as a parameter for the frame id
     */

    void final_destination(int i);

    /**
     * @brief Callback for Aruco Markers Subscriber
     * 
     */

    void cb1(const std::shared_ptr<ros2_aruco_interfaces::msg::ArucoMarkers> aruco);

    /**
     * @brief Subscriber Callback for goal reached 
     * 
     */

    void timer_callback(const std::shared_ptr<std_msgs::msg::Bool> msg);

    /**
     * @brief Callback for transform listner
     * 
     */

    void cb2();
};