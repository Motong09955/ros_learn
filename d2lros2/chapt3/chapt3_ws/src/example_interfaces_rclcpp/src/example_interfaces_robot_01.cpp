#include "rclcpp/rclcpp.hpp"
#include "example_ros2_interfaces/msg/robot_status.hpp"
#include "example_ros2_interfaces/srv/move_robot.hpp"

/*
测试指令：  ros2 service call /move_robot example_ros2_interfaces/srv/MOveRobot "{distance: 5}"
*/

//创建一个机器人类
class Robot
{
  public:
    Robot() = default;
    ~Robot() = default;

    float move_distance(float distance)
    {
      /*
      brief : 移动指定的距离

      parma :
        distance:float 移动的距离

      return: float 当前的位置
      */
      status_ = example_ros2_interfaces::msg::RobotStatus::STATUS_MOVING;
      target_pose_ += distance;

      while(fabs(target_pose_ - current_pose_) >= 0.01)
      {
        float step = distance / fabs(distance) * fabs(target_pose_ - current_pose_) * 0.1;
        current_pose_ += step;
        std::cout << "移动了: " << step << "当前位置" << current_pose_ << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
      }
      status_ = example_ros2_interfaces::msg::RobotStatus::STATUS_STOP;
      return current_pose_;
    }

    float get_current_pose()
    {
      // """
      // 获取当前位置
      // """
      return current_pose_;
    }

    float get_status()
    {
      // """
      // 获取当前状态
      // """
      return status_;
    }

  private:
    //当前位置
    float current_pose_ = 0.0;
    //目标位置
    float target_pose_ =0.0;
    int status_ = example_ros2_interfaces::msg::RobotStatus::STATUS_STOP;
};

class ExampleInterfacesRobot : public rclcpp::Node
{
  public:
    ExampleInterfacesRobot(std::string name) : Node(name)
    {
      RCLCPP_INFO(this->get_logger(), "节点已启动:%s",name.c_str());
      //创建move_robot服务
      move_robot_server_ = this->create_service<example_ros2_interfaces::srv::MoveRobot>(
        "move_robot",std::bind(&ExampleInterfacesRobot::handle_move_robot,this,
                              std::placeholders::_1,std::placeholders::_2
        ) 
      );
      //创建发布者
      robot_status_publisher_ = this->create_publisher<example_ros2_interfaces::msg::RobotStatus>(
        "robot_status",10
      );
      //创建定时器，500ms
      timer_ = this->create_wall_timer(
        std::chrono::milliseconds(500),std::bind(&ExampleInterfacesRobot::timer_callback,this)
      );

    }   

    private:
    Robot robot;
    //定义定时器，用于定时发布机器人位置
    rclcpp::TimerBase::SharedPtr timer_;
    //定义共享指针，移动机器人服务
    rclcpp::Service<example_ros2_interfaces::srv::MoveRobot>::SharedPtr move_robot_server_;
    //定义共享指针，机器人状态发布者
    rclcpp::Publisher<example_ros2_interfaces::msg::RobotStatus>::SharedPtr robot_status_publisher_;

    void timer_callback()
    {
      // """
      // 500ms定时回调函数
      // """
      example_ros2_interfaces::msg::RobotStatus message;
      message.status = robot.get_status();
      message.pose = robot.get_current_pose();
      RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", robot.get_current_pose());
      //发布机器人状态
      robot_status_publisher_->publish(message);
    }

    void handle_move_robot(const std::shared_ptr<example_ros2_interfaces::srv::MoveRobot::Request> request,
                          std::shared_ptr<example_ros2_interfaces::srv::MoveRobot::Response> response)
    {
      // """
      // 收到话题时的回调函数
      // @parma 
      //   request : 请求共享指针，包含移动数据
      //   response : 响应共享指针，包含当前位置信息
      // """
      RCLCPP_INFO(this->get_logger(),"收到请求移动距离:%f,当前位置:%f",request->distance,robot.get_current_pose());
      robot.move_distance(request->distance);
      response->pose = robot.get_current_pose();
    }
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<ExampleInterfacesRobot>("example_interfaces_robot_01");
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}