
#! /usr/bin/env python3

import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, SetEnvironmentVariable
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node



def generate_launch_description():
    executable = 'av_camera'
    package_name = 'av_camera'
    
    return LaunchDescription([
        # camera1 node
        Node(
            package='av_camera',
            executable='av_camera',
            output='screen',
            name = "camera1", # node name remapping
            parameters=[{    # parameters for the node
                'camera_name': "blind_spot_left",
                'camera_frequency': 79.0,
                'camera_bandwidth': 4,
            }],
            remappings=[('/camera_image', '/camera1_image')]),
        
        # camera2 node
        Node(
            package='av_camera',
            executable='av_camera',
            output='screen',
            name="camera2",  # node name remapping
            parameters=[{    # parameters for the node
                'camera_name': "front_center",
                'camera_frequency': 24.0,
                'camera_bandwidth': 1,
            }],
            remappings=[('/camera_image', '/camera2_image')]),
        
        # camera3 node
        Node(
            package='av_camera',
            executable='av_camera',
            output='screen',
            name="camera3",  # node name remapping
            parameters=[{    # parameters for the node
                'camera_name': "blind_spot_right",
                'camera_frequency': 79.0,
                'camera_bandwidth': 4,
            }],
            remappings=[('/camera_image', '/camera3_image')]),
        
        # camera4 node
        Node(
            package='av_camera',
            executable='av_camera',
            output='screen',
            name="camera4",  # node name remapping
            parameters=[{    # parameters for the node
                'camera_name': "rear_center",
                'camera_frequency': 77.0,
                'camera_bandwidth': 4,
            }],
            remappings=[('/camera_image', '/camera4_image')]),

    ])
