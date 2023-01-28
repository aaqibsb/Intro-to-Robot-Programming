# Copyright (c) 2018 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
Example for spawing multiple robots in Gazebo.

This is an example on how to create a launch file for spawning multiple robots into Gazebo
and launch multiple instances of the navigation stack, each controlling one robot.
The robots co-exist on a shared environment and are controlled by independent nav stacks
"""

import os
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import (DeclareLaunchArgument, ExecuteProcess, GroupAction,
                            IncludeLaunchDescription, LogInfo)
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, TextSubstitution
from nav2_common.launch import HasNodeParams, RewrittenYaml


def generate_launch_description():
    # Get the launch directory
    bringup_dir = get_package_share_directory('tb3_bringup')
    launch_dir = os.path.join(bringup_dir, 'launch')

    # Names and poses of the robots
    robots = [
        {'name': 'robot1', 'x_pose': 3.0, 'y_pose': 0.0,
            'z_pose': 0.01, 'yaw_pose': 0.0},
        # {'name': 'robot2', 'x_pose': 9.0, 'y_pose': -4.0,
        #     'z_pose': 0.01, 'yaw_pose': -1.57},
        # {'name': 'robot3', 'x_pose': -4.0, 'y_pose': 0.0, 'z_pose': 0.01, 'yaw_pose': 3.14}
        ]

    # Simulation settings
    world = LaunchConfiguration('world')
    simulator = LaunchConfiguration('simulator')

    # On this example all robots are launched with the same settings
    map_yaml_file = LaunchConfiguration('map')

    autostart = LaunchConfiguration('autostart')
    aruco_id = LaunchConfiguration('aruco_id')
    rviz_config_file = os.path.join(
        bringup_dir, 'rviz', 'robots.rviz')
    use_robot_state_pub = LaunchConfiguration('use_robot_state_pub')
    use_rviz = LaunchConfiguration('use_rviz')
    log_settings = LaunchConfiguration('log_settings', default='true')

    # Declare the launch arguments
    declare_world_cmd = DeclareLaunchArgument(
        'world',
        default_value=os.path.join(bringup_dir, 'worlds', 'empty_world.world'),
        description='Full path to world file to load')
    
    declare_aruco_cmd = DeclareLaunchArgument(
        'aruco_id',
        default_value='0',
        description='ID for the aruco fiducial marker')

    declare_simulator_cmd = DeclareLaunchArgument(
        'simulator',
        default_value='gazebo',
        description='The simulator to use (gazebo or gzserver)')

    declare_map_yaml_cmd = DeclareLaunchArgument(
        'map',
        default_value=os.path.join(bringup_dir, 'maps', 'turtlebot3_world.yaml'),
        description='Full path to map file to load')

    
    declare_robot1_params_file_cmd = DeclareLaunchArgument(
        'robot1_params_file',
        default_value=os.path.join(bringup_dir, 'params', 'nav2_multirobot_params_1.yaml'),
        description='Full path to the ROS2 parameters file to use for robot1 launched nodes')

    declare_robot2_params_file_cmd = DeclareLaunchArgument(
        'robot2_params_file',
        default_value=os.path.join(bringup_dir, 'params', 'nav2_multirobot_params_2.yaml'),
        description='Full path to the ROS2 parameters file to use for robot2 launched nodes')
    
    declare_robot3_params_file_cmd = DeclareLaunchArgument(
        'robot3_params_file',
        default_value=os.path.join(
            bringup_dir, 'params', 'nav2_multirobot_params_3.yaml'),
        description='Full path to the ROS2 parameters file to use for robot2 launched nodes')

    declare_autostart_cmd = DeclareLaunchArgument(
        'autostart', default_value='false',
        description='Automatically startup the stacks')

    declare_rviz_config_file_cmd = DeclareLaunchArgument(
        'rviz_config',
        default_value=os.path.join(bringup_dir, 'rviz', 'nav2_namespaced_view.rviz'),
        description='Full path to the RVIZ config file to use.')

    declare_use_robot_state_pub_cmd = DeclareLaunchArgument(
        'use_robot_state_pub',
        default_value='True',
        description='Whether to start the robot state publisher')

    declare_use_rviz_cmd = DeclareLaunchArgument(
        'use_rviz',
        default_value='True',
        description='Whether to start RVIZ')

    # Start Gazebo with plugin providing the robot spawing service
    start_gazebo_cmd = ExecuteProcess(
        cmd=[simulator, '--verbose', '-s', 'libgazebo_ros_init.so',
                                     '-s', 'libgazebo_ros_factory.so', world],
        output='screen')
    
    start_rviz_cmd = IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                    os.path.join(launch_dir, 'rviz_launch.py')),
            condition=IfCondition(use_rviz),
            launch_arguments={
                            #   'namespace': TextSubstitution(text=robot['name']),
                            #   'use_namespace': 'True',
                              'rviz_config': rviz_config_file}.items())
    
    start_odom_updater_cmd = Node(
        package='odom_updater',
        executable='odom_updater',
        output='screen')
    
    start_world_odom_broadcaster_cmd = Node(
        package='world_odom_broadcaster',
        executable='world_odom_broadcaster',
        output='screen')
    
    final_project_params = os.path.join(
        get_package_share_directory('target_reacher'),
        'params',
        'final_params.yaml'
    )
    
    start_target_reacher = Node(
        package='target_reacher',
        executable='target_reacher',
        parameters=[final_project_params],
        output='screen')
    
    start_aruco_detection_node_cmd = Node(
        package='ros2_aruco',
        executable='aruco_node',
        output='screen')

    # Define commands for spawing the rnamespaceobots into Gazebo
    spawn_robots_cmds = []
    for robot in robots:
        spawn_robots_cmds.append(
            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(os.path.join(bringup_dir, 'launch',
                                                           'spawn_tb3_launch.py')),
                launch_arguments={
                                  'x_pose': TextSubstitution(text=str(robot['x_pose'])),
                                  'y_pose': TextSubstitution(text=str(robot['y_pose'])),
                                  'z_pose': TextSubstitution(text=str(robot['z_pose'])),
                                  'yaw_pose': TextSubstitution(text=str(robot['yaw_pose'])),
                                  'robot_name': robot['name'],
                                  'turtlebot_type': TextSubstitution(text='waffle'),
                                  'aruco_id': aruco_id,
                                  }.items()))

    # Define commands for launching the navigation instances
    nav_instances_cmds = []
    for robot in robots:
        params_file = LaunchConfiguration(f"{robot['name']}_params_file")

        group = GroupAction([
            # IncludeLaunchDescription(
            #     PythonLaunchDescriptionSource(
            #             os.path.join(launch_dir, 'rviz_launch.py')),
            #     condition=IfCondition(use_rviz),
            #     launch_arguments={
            #                       'namespace': TextSubstitution(text=robot['name']),
            #                       'use_namespace': 'True',
            #                       'rviz_config': rviz_config_file}.items()),

            IncludeLaunchDescription(
                PythonLaunchDescriptionSource(os.path.join(bringup_dir,
                                                           'launch',
                                                           'tb3_simulation_launch.py')),
                launch_arguments={'namespace': robot['name'],
                                  'use_namespace': 'True',
                                  'map': map_yaml_file,
                                  'use_sim_time': 'True',
                                  'params_file': params_file,
                                  'autostart': autostart,
                                  'use_rviz': 'False',
                                  'frame_prefix': robot['name']+ '/',
                                  'use_simulator': 'False',
                                  'headless': 'False',
                                  'use_robot_state_pub': use_robot_state_pub}.items()),

            LogInfo(
                condition=IfCondition(log_settings),
                msg=['Launching ', robot['name']]),
            LogInfo(
                condition=IfCondition(log_settings),
                msg=[robot['name'], ' map yaml: ', map_yaml_file]),
            LogInfo(
                condition=IfCondition(log_settings),
                msg=[robot['name'], ' params yaml: ', params_file]),
            LogInfo(
                condition=IfCondition(log_settings),
                msg=[robot['name'], ' rviz config file: ', rviz_config_file]),
            LogInfo(
                condition=IfCondition(log_settings),
                msg=[robot['name'], ' using robot state pub: ', use_robot_state_pub]),
            LogInfo(
                condition=IfCondition(log_settings),
                msg=[robot['name'], ' autostart: ', autostart])
        ])

        nav_instances_cmds.append(group)

    # Create the launch description and populate
    ld = LaunchDescription()

    # Declare the launch options
    ld.add_action(declare_simulator_cmd)
    ld.add_action(declare_world_cmd)
    ld.add_action(declare_aruco_cmd)
    ld.add_action(declare_map_yaml_cmd)
    ld.add_action(declare_robot1_params_file_cmd)
    ld.add_action(declare_robot2_params_file_cmd)
    ld.add_action(declare_robot3_params_file_cmd)
    ld.add_action(declare_use_rviz_cmd)
    ld.add_action(declare_autostart_cmd)
    ld.add_action(declare_rviz_config_file_cmd)
    ld.add_action(declare_use_robot_state_pub_cmd)

    # Add the actions to start gazebo, robots and simulations
    

    for spawn_robot_cmd in spawn_robots_cmds:
        ld.add_action(spawn_robot_cmd)

    for simulation_instance_cmd in nav_instances_cmds:
        ld.add_action(simulation_instance_cmd)
        
    ld.add_action(start_odom_updater_cmd)
    ld.add_action(start_world_odom_broadcaster_cmd)
    ld.add_action(start_aruco_detection_node_cmd)
    ld.add_action(start_target_reacher)
    
    ld.add_action(start_gazebo_cmd)
    ld.add_action(start_rviz_cmd)

    return ld
