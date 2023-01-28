#include <rclcpp/rclcpp.hpp>
#include "world_odom_broadcaster.h"

int main(int argc, char *argv[])
{
    // init
    rclcpp::init(argc, argv);
    // node
    auto node = std::make_shared<WorldOdomBroadcaster>("world_odom_broadcaster");
    rclcpp::spin(node);
    // shutdown
    rclcpp::shutdown();
}