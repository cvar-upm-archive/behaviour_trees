from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration, EnvironmentVariable, PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('drone_id', description="Drone namespace", 
                              default_value=EnvironmentVariable('AEROSTACK2_SIMULATION_DRONE_ID')),
        DeclareLaunchArgument('use_sim_time', description="Use sim time flag", default_value='false'),
        DeclareLaunchArgument('tree', description="Path to XML Behaviour Tree"),
        DeclareLaunchArgument('groot_logger', description="Want to use groot logger?",
                              choices={"true", "false"}, default_value='false'),
        DeclareLaunchArgument('groot_client_port', description="Groot publisher port", default_value='1666'),
        DeclareLaunchArgument('groot_server_port', description="Groot server port", default_value='1667'),
        DeclareLaunchArgument('server_timeout', description="Server timeout (ms). Minimum 10000.", default_value='10000'),
        DeclareLaunchArgument('bt_loop_duration', description="Bt loop duration (ms). Minimum 10.", default_value='10'),

        Node(
            package="behaviour_trees",
            executable="behaviour_trees_main",
            namespace=LaunchConfiguration('drone_id'),
            parameters=[{'use_sim_time': LaunchConfiguration('use_sim_time'),
                         'tree': LaunchConfiguration('tree'),
                         'use_groot': LaunchConfiguration('groot_logger'),
                         'groot_client_port': LaunchConfiguration('groot_client_port'),
                         'groot_server_port': LaunchConfiguration('groot_server_port'),
                         'server_timeout': LaunchConfiguration('server_timeout'),
                         'bt_loop_duration': LaunchConfiguration('bt_loop_duration')}],
            output="screen",
            emulate_tty=True,
            # arguments=['--ros-args', '--log-level', 'DEBUG']
        ),
    ])
