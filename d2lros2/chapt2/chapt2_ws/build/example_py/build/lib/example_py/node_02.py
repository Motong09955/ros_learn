import rclpy
from rclpy.node import Node
def main(args=None):
    rclpy.init()
    node = Node("node_02")
    node.get_logger().info("大家好，我是node_02")
    rclpy.spin(node)
    rclpy.shutdown()