import rclpy
# 导入rclpy库
from rclpy.node import Node

rclpy.init()
# 调用rclpy的初始化函数
rclpy.spin(Node("second_node"))
# 调用rclcpp的循环运行创建的second_node节点
