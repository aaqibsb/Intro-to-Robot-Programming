#include <rclcpp/rclcpp.hpp>
#include "bot_controller/bot_controller.h"

int main(int argc, char *argv[])
{
    // init
    // rclcpp::init(argc, argv);
    // // node
    // auto node = std::make_shared<BotController>("bot_controller", "robot");
    // rclcpp::spin(node);
    // // shutdown
    // rclcpp::shutdown();

    rclcpp::executors::MultiThreadedExecutor exec;
    auto node = std::make_shared<BotController>("bot_controller", "robot");
    exec.add_node(node);
    exec.spin();
    rclcpp::shutdown();
}