import rclpy
from rclpy.node import Node
from example_ros2_interfaces.srv import MoveRobot
from example_ros2_interfaces.msg import RobotStatus

class ExampleInterfacesControl02(Node):
    def __init__(self,name):
        super().__init__(name)
        self.get_logger().info("节点已启动%s"%name)
        self.client_ = self.create_client(MoveRobot,"move_robot")
        self.robot_status_subscribe_ = self.create_subscription(RobotStatus,"robot_status",self.robot_status_callback,10)

    def robot_status_callback(self,msg):
         self.get_logger().info(f"当前机器人状态：{msg.status}，当前位置：{msg.pose}")

    def move_result_callback_(self,result_future):
         response = result_future.result()
         self.get_logger().info(f"机器人移动结果：{response.pose}")

    def move_robot(self,distance):
        while rclpy.ok() and self.client_.wait_for_service(timeout_sec=1.0) == False:
            self.get_logger().info("等待服务启动")
        request = MoveRobot.Request()
        request.distance = distance
        self.get_logger().info(f"请求服务让机器人移动：{request.distance}")
        self.client_.call_async(request).add_done_callback(self.move_result_callback_)
    
def main(args=None):
        rclpy.init(args=args)
        node = ExampleInterfacesControl02("example_interfaces_control_02")
        node.move_robot(5.0)
        rclpy.spin(node)
        rclpy.shutdown()