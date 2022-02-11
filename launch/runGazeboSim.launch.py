import os
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    # Find path to gazebo_ros
    pkgGazeboROS = FindPackageShare(package="gazebo_ros").find("gazebo_ros")

    # Start gazebo
    startGazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkgGazeboROS, "launch", "gazebo.launch.py")
        )
    )

    # Start compControlTorque node
    startCompControlTorque = Node(
        package="drone_controller",
        executable="compControlTorque",
        name="torque",
    )

    # Create LaunchDescription object
    ld = LaunchDescription()

    # Add all actions to the LaunchDescription object
    ld.add_action(startGazebo)
    ld.add_action(startCompControlTorque)

    return ld
