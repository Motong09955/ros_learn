#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class TopicSubscriber01 : public rclcpp::Node
{
    public:
        //构造函数
        TopicSubscriber01(std::string name) : Node(name)
        {
            RCLCPP_INFO(this->get_logger(),"大家好，我是%s",name.c_str());
            command_subscriber_ = this->create_subscription<std_msgs::msg::String>
                        ("command",10,std::bind(&TopicSubscriber01::command_callback,
                        this,std::placeholders::_1));  
        }
    private:
        //声明一个订阅者
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscriber_;
        void command_callback(const std_msgs::msg::String::SharedPtr msg)
        {  
            double speed = 0.0f;
            if(msg->data == "forward")
            {
                speed = 0.2f;
            }
            RCLCPP_INFO(this->get_logger(),"收到[%s]命令，发送速度 %f"
                        ,msg->data.c_str(),speed);
        }
};

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    //创建对应节点的共享指针对象
    auto node = std::make_shared<TopicSubscriber01>("topic_subscriber_01");

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}