from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    return LaunchDescription(
        [
            Node(
                package="drone_controller",
                executable="compControlTorque",
                name="torque",
            )
        ]
    )
