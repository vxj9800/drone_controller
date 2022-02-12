import os
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.actions import ExecuteProcess
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    # Find the path of the share folder of current package
    sharePath = FindPackageShare(package="drone_controller").find("drone_controller")

    # Add path to the gazebo models to the GAZEBO_MODEL_PATH environment
    os.environ["GAZEBO_MODEL_PATH"] = os.path.join(sharePath, "gazebo", "models")

    # Define path to the world file
    worldPath = os.path.join(sharePath, "gazebo", "worlds", "classic.world")

    # Start gazebo
    startGazebo = ExecuteProcess(
        cmd=["gazebo", "--verbose", worldPath, "-u"], output="screen"
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
