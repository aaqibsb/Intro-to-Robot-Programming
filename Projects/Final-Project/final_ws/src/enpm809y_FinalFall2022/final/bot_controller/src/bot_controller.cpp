#include <rclcpp/rclcpp.hpp>
#include "bot_controller/bot_controller.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"
#include "tf2/exceptions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include <geometry_msgs/msg/transform_stamped.hpp>

void BotController::transform_callback()
{
    if (!m_go_to_goal)
        return;

    geometry_msgs::msg::TransformStamped t;

    // RCLCPP_INFO(this->get_logger(), "Transform callback");

    try
    {
        t = m_tf_buffer->lookupTransform(m_parent_frame, m_child_frame, tf2::TimePointZero);
    }
    catch (const tf2::TransformException &ex)
    {
        RCLCPP_INFO_STREAM(
            this->get_logger(), "Could not transform " << m_parent_frame << " to " << m_child_frame << ": " << ex.what());
        return;
    }

    // RCLCPP_INFO(
    //     this->get_logger(), "Position of robot in odom: [%f, %f]", t.transform.translation.x, t.transform.translation.y);

    m_location.first = t.transform.translation.x;
    m_location.second = t.transform.translation.y;
    m_orientation = t.transform.rotation;

    // if (!m_goal_set)
    // {
    //     RCLCPP_INFO(this->get_logger(), "Robot has been localized, going to goal.");
    //     go_to_goal();
    // }
}

double BotController::normalize_angle_positive(double angle)
{
    const double result = fmod(angle, 2.0 * M_PI);
    if (result < 0)
        return result + 2.0 * M_PI;
    return result;
}

double BotController::normalize_angle(double angle)
{
    const double result = fmod(angle + M_PI, 2.0 * M_PI);
    if (result <= 0.0)
        return result + M_PI;
    return result - M_PI;
}

double BotController::compute_distance(const std::pair<double, double> &a, const std::pair<double, double> &b)
{
    return sqrt(pow(b.first - a.first, 2) + pow(b.second - a.second, 2));
}

double BotController::compute_yaw_from_quaternion()
{
    tf2::Quaternion q(
        m_orientation.x,
        m_orientation.y,
        m_orientation.z,
        m_orientation.w);
    tf2::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);

    return yaw;
}

void BotController::move(double linear, double angular)
{
    geometry_msgs::msg::Twist msg;
    msg.linear.x = linear;
    msg.angular.z = angular;
    m_publisher_cmd_vel->publish(msg);
}

void BotController::stop()
{
    m_go_to_goal = false;
    geometry_msgs::msg::Twist cmd_vel_msg;
    cmd_vel_msg.linear.x = 0;
    cmd_vel_msg.angular.z = 0;
    m_publisher_cmd_vel->publish(cmd_vel_msg);

    std_msgs::msg::Bool goal_reached_msg;
    goal_reached_msg.data = true;
    m_goal_reached_publisher->publish(goal_reached_msg);

    
}

void BotController::go_to_goal_callback()
{

    // RCLCPP_INFO_STREAM(this->get_logger(), "go_to_goal_callback");
    // if (m_location.first == 3.0 && m_location.second == 0)
    // {
    //     RCLCPP_INFO(this->get_logger(), "Robot is not localized yet");
    //     return;
    // }

    if (!m_go_to_goal)
        return;

    std::pair<double, double> goal{m_goal_x, m_goal_y};
    double distance_to_goal = compute_distance(m_location, goal);

    // RCLCPP_INFO_STREAM(this->get_logger(), "Current position: [" << m_location.first << "," << m_location.second << "]");

    if (distance_to_goal > 0.1)
    {
        distance_to_goal = compute_distance(m_location, goal);
        double angle_to_goal = std::atan2(m_goal_y - m_location.second, m_goal_x - m_location.first);
        // RCLCPP_INFO_STREAM(this->get_logger(), "Distance to goal: [" << distance_to_goal << "]");

        if (angle_to_goal < 0)
            // angle_to_goal = 2 * M_PI + angle_to_goal;
            angle_to_goal = normalize_angle_positive(angle_to_goal);

        // angle to rotate to face the goal
        double w = angle_to_goal - compute_yaw_from_quaternion();

        if (w > M_PI)
        {
            w = w - 2 * M_PI;
            // w = m_normalize_angle_positive(w);
        }

        // proportional control for linear velocity
        double linear_x = std::min(m_kv * distance_to_goal, m_linear_speed);

        // proportional control for angular velocity
        double angular_z = m_kh * w;
        if (angular_z > 0)
            angular_z = std::min(angular_z, m_angular_speed);
        else
            angular_z = std::max(angular_z, -m_angular_speed);

        move(linear_x, angular_z);
    }
    else
    {
        RCLCPP_INFO_STREAM(this->get_logger(), "********** Goal reached **********");
        stop();
    }
}