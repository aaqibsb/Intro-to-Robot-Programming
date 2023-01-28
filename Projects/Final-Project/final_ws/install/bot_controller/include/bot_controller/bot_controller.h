#pragma once

#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <std_msgs/msg/bool.hpp>
#include <geometry_msgs/msg/quaternion.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <string>
#include "tf2/exceptions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

/**
 * @brief The BotController class.
 *
 * This class contains a feedback loop control method to move the robot to a goal position.
 *
 */
class BotController : public rclcpp::Node
{
public:
    BotController(std::string node_name,
                  std::string robot_name,
                  bool go_to_goal = false,
                  double linear_speed = 0.5,
                  double angular_speed = 0.3) : Node(node_name),
                                                m_robot_name{robot_name},
                                                m_go_to_goal{go_to_goal},
                                                m_linear_speed{linear_speed},
                                                m_angular_speed{angular_speed},
                                                m_roll{0},
                                                m_pitch{0},
                                                m_yaw{0},
                                                m_kv{1},
                                                m_kh{1},
                                                m_goal_x{0.0},
                                                m_goal_y{0.0}
                                                // m_distance_to_goal{1.0}, 
                                                // m_goal_set{false}
    {
        auto current_location = std::make_pair<double, double>(3.0, 0.0);
        m_location = current_location;
        m_cbg = this->create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);

        auto command_topic_name = "/" + m_robot_name + "/cmd_vel";
        // auto pose_topic_name = "/" + m_robot_name + "/odom";

        RCLCPP_INFO_STREAM(this->get_logger(), "BotController Constructor");
        m_publisher_cmd_vel = this->create_publisher<geometry_msgs::msg::Twist>(command_topic_name, 10);
        m_goal_reached_publisher = this->create_publisher<std_msgs::msg::Bool>("goal_reached", 10);
        // m_subscriber_robot3_pose = this->create_subscription<nav_msgs::msg::Odometry>(pose_topic_name, 10, std::bind(&BotController::robot_pose_callback, this, std::placeholders::_1));
        m_parent_frame = "" + m_robot_name + "/odom";
        m_child_frame = "" + m_robot_name + "/base_footprint";

        m_tf_buffer = std::make_unique<tf2_ros::Buffer>(this->get_clock());
        m_tf_listener = std::make_shared<tf2_ros::TransformListener>(*m_tf_buffer);

        // Call on_timer function 5 times per second
        m_transform_timer = this->create_wall_timer(std::chrono::milliseconds((int)(1000.0 / 5)), std::bind(&BotController::transform_callback, this), m_cbg);
        m_go_to_goal_timer = this->create_wall_timer(std::chrono::milliseconds((int)(1000.0 / 1)), std::bind(&BotController::go_to_goal_callback, this), m_cbg);
    }

    // /**
    //  * @brief Move a robot to a goal position.
    //  */
    // void go_to_goal();

    /**
     * @brief Set the goal to reach.
     *
     * @param go_to_goal Flag used to perform a transform listener
     * @param x x-coordinate of the goal position.
     * @param y y-coordinate of the goal position.
     */
    void set_goal(double x, double y)
    {
        m_go_to_goal = true;
        m_goal_x = x;
        m_goal_y = y;
        RCLCPP_INFO_STREAM(this->get_logger(), "Going to goal: [" << m_goal_x << "," << m_goal_y << "]");
    }

    void stop();

private:
    // attributes
    std::string m_robot_name;
    bool m_go_to_goal;
    double m_linear_speed;
    double m_angular_speed;
    double m_roll;  // rad
    double m_pitch; // rad
    double m_yaw;   // rad
    double m_kv;    // gain for linear velocity
    double m_kh;    // gain for angular velocity
    double m_goal_x;
    double m_goal_y;
    double m_distance_to_goal;
    // bool m_goal_set;
    rclcpp::CallbackGroup::SharedPtr m_cbg;
    rclcpp::TimerBase::SharedPtr m_timer;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr m_publisher_cmd_vel;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr m_goal_reached_publisher;
    // rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr m_subscriber_robot3_pose;
    std::string m_parent_frame;
    std::string m_child_frame;
    std::pair<double, double> m_location;
    geometry_msgs::msg::Quaternion m_orientation;
    rclcpp::TimerBase::SharedPtr m_transform_timer;
    rclcpp::TimerBase::SharedPtr m_go_to_goal_timer;
    rclcpp::TimerBase::SharedPtr m_move_in_circle_timer;
    std::shared_ptr<tf2_ros::TransformListener> m_tf_listener;
    std::unique_ptr<tf2_ros::Buffer> m_tf_buffer;

    /**
     * @brief Compute the distance between two points.
     *
     * @param a The first point.
     * @param b The second point.
     * @return double   The distance between a and b.
     */
    double compute_distance(const std::pair<double, double> &a, const std::pair<double, double> &b);

    /**
     * @brief Callback function for the robot3 pose.
     *
     * @param msg Odometry message.
     */
    void robot_pose_callback(const nav_msgs::msg::Odometry::SharedPtr msg);
    /**
     * @brief Normalizes the angle to be 0 to 2*M_PI
     *
     * @param angle Angle to normalize (rad)
     * @return double Normalized angle (rad)
     */
    double normalize_angle_positive(double angle);

    /**
     * @brief Normalizes the angle to be -M_PI circle to +M_PI circle
     *
     * @param angle Angle to normalize (rad)
     * @return double Normalized angle (rad)
     */
    double normalize_angle(double angle);

    double compute_yaw_from_quaternion();
    void move(double linear, double angular);
    
    void transform_callback();
    void go_to_goal_callback();
    void move_in_circle_callback();
};
