#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class NodeSubscriber02(Node):
    def __init__(self, name):
        super().__init__(name)
        """
        super取到父类的代理，这里就是调用父类“Node”的__init__方法，并把name传入给它
        Node的构造函数负责把这个对象注册进ROS图，建立日志器，准备系统参数等基础工作
        """
        self.get_logger().info("大家好，我是%s" % name)
        self.command_subscribe_ = self.create_subscription(
            String, "command", self.command_callback, 10)

    def command_callback(self, msg):
        speed = 0.0
        if msg.data == "backup":
            speed = 0.5
        self.get_logger().info(f"收到[{msg.data}]命令，发送速度{speed}")


def main(args=None):
    rclpy.init(args=args)
    node = NodeSubscriber02("topic_subscribe_02")
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
