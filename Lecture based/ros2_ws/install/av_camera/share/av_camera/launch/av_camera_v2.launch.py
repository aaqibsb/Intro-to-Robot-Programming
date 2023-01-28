
#! /usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    ld = LaunchDescription()
    # camera1 node
    camera1_node = Node(
        package='av_camera',
        executable='av_camera',
        output='screen',
        name="camera1",  # node name remapping
        parameters=[{    # parameters for the node
            'camera_name': "blind_spot_left",
                'camera_frequency': 79.0,
                'camera_bandwidth': 4,
        }],
        remappings=[('/camera_image', '/camera1_image')])
    # camera2 node
    camera2_node = Node(
        package='av_camera',
        executable='av_camera',
        output='screen',
        name="camera2",  # node name remapping
        parameters=[{    # parameters for the node
            'camera_name': "front_center",
                'camera_frequency': 24.0,
                'camera_bandwidth': 1,
        }],
        remappings=[('/camera_image', '/camera2_image')])

    # camera3 node
    camera3_node = Node(
        package='av_camera',
        executable='av_camera',
        output='screen',
        name="camera3",  # node name remapping
        parameters=[{    # parameters for the node
                'camera_name': "blind_spot_right",
                'camera_frequency': 79.0,
                'camera_bandwidth': 4,
        }],
        remappings=[('/camera_image', '/camera3_image')])

    camera4_node = Node(
        package='av_camera',
        executable='av_camera',
        output='screen',
        name="camera4",  # node name remapping
        parameters=[{    # parameters for the node
                'camera_name': "rear_center",
                'camera_frequency': 77.0,
                'camera_bandwidth': 4,
        }],
        remappings=[('/camera_image', '/camera4_image')])

    ld.add_action(camera1_node)
    ld.add_action(camera2_node)
    ld.add_action(camera3_node)
    ld.add_action(camera4_node)

    return ld
