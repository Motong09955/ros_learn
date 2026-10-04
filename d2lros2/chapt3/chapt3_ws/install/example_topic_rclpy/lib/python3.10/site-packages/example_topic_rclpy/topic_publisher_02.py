#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class NodePublisher02(Node):
    def __init__(self, name):
        super().__init__(name)
        self.get_logger().info("大家好，我是%s" % name)
        self.command_publisher_ = self.create_publisher(String, "command", 10)
        self.timer = self.create_timer(0.5, self.timer_callback)

    def timer_callback(self):
        msg = String()
        msg.data = 'backup'
        self.command_publisher_.publish(msg)
        self.get_logger().info(f'发布了指令: {msg.data}')


def main(args=None):
    rclpy.init(args=args)
    node = NodePublisher02("topic_publisher_02")
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
