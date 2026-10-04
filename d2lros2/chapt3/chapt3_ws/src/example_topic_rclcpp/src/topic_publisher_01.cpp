#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"//导入消息接口类型的头文件

class TopicPublisher01 : public rclcpp::Node
{
    public://构造函数,输入参数为节点名称
        TopicPublisher01(std::string name):Node(name)
        {
            /*this->get_logger()负责打印日志消息，
            name.c_str()将字符串name转换为C风格字符串*/
            RCLCPP_INFO(this->get_logger(),"大家好，我是%s.",name.c_str());
            //创建话题发布者,<std_msgs::msg::String>指定消息类型，"command"指定话题名称
            // 10默认指代KeepLast的数值，表示保存最近的10条消息
            command_publisher_ = 
                    this->create_publisher<std_msgs::msg::String>("command",10);
            //创建定时器，定时发布消息，bind部分用于将"成员函数"和"要调用它的对象"捆在一起，
            //做成一个可以直接调用的整体，作为定时器的回调交出去
            timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
                    std::bind(&TopicPublisher01::timer_callback,this));
        }
    private:
        void timer_callback()
        {
            //创建消息
            std_msgs::msg::String message;
            message.data = "forward";
            //日志打印
            RCLCPP_INFO(this->get_logger(),"Publishing: '%s'"
                                                    ,message.data.c_str());
            //发布消息
            command_publisher_->publish(message);
        }
        //声明定时器指针
        rclcpp::TimerBase::SharedPtr timer_;
        //声明话题发布者
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr command_publisher_;
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    //创建对应节点的共享指针对象
    auto node = std::make_shared<TopicPublisher01>("topic_publisher_01");
    //运行节点并检测退出信号
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}