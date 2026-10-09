#include <chrono>
#include "rclcpp/rclcpp.hpp"

class ParametersBasicNode : public rclcpp::Node
{
    public:
        explicit ParametersBasicNode(std::string name) : Node(name)
        {
            RCLCPP_INFO(this->get_logger(), "节点已启动: %s", name.c_str());
            //声明参数函数，设定了一个名为"rcl_log_level"的参数，默认值为0，
            //注意declare_paramter函数与declare_parameters函数的区别，declare_parameters函数可以声明多个参数
            this->declare_parameter("rcl_log_level", 0);
            //这里使用的是get_parameter函数的无模板布尔返回值类型，当参数存在时返回true，并且把值赋给输入的第二个参数，否则返回false
            this->get_parameter("rcl_log_level", this->log_level);
            //设置日志级别
            this->get_logger().set_level(rclcpp::Logger::Level(log_level));
            using namespace std::literals::chrono_literals;
            timer_ = this->create_wall_timer(500ms,
                                             std::bind(&ParametersBasicNode::timer_callback, this));
        }

    private:
        int log_level;
        rclcpp::TimerBase::SharedPtr timer_;

        void timer_callback()
        {
            this->get_parameter("rcl_log_level", log_level);
            //设置日志级别
            this->get_logger().set_level(rclcpp::Logger::Level(log_level));
            std::cout << "=================================================================" << std::endl;
            RCLCPP_DEBUG(this->get_logger(), "我是DEBUG级别的日志");
            RCLCPP_INFO(this->get_logger(), "我是INFO级别的日志");
            RCLCPP_WARN(this->get_logger(), "我是WARN级别的日志");
            RCLCPP_ERROR(this->get_logger(), "我是ERROR级别的日志");
            RCLCPP_FATAL(this->get_logger(), "我是FATAL级别的日志");
        }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ParametersBasicNode>("parameters_basic");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}