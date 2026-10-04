import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/motong/ros_learn/d2lros2/chapt2/colcon_test_ws/install/examples_rclpy_minimal_action_server'
