import os
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.actions import ExecuteProcess
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    # Find the path of the share folder of current package
    quadSharePath = FindPackageShare(package="my_quad").find("my_quad")

    # Include the launch file of my_quad package
    runQuadSim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(quadSharePath, "launch", "runGazeboSim.launch.py")
        )
    )

    # Start compControlTorque node
    startCompControlTorque = Node(
        package="drone_controller", executable="compControlTorque"
    )

    # Create LaunchDescription object
    ld = LaunchDescription()

    # Add all actions to the LaunchDescription object
    ld.add_action(runQuadSim)
    ld.add_action(startCompControlTorque)

    return ld
