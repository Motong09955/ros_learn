#include "rclcpp/rclcpp.hpp"
using namespace rclcpp;
using namespace std;

int main(int argc,char **argv)
{
    // 初始化rclcpp
    init(argc,argv);
    // 产生一个node_01节点
    auto node = make_shared<Node>("node_01");
    // 打印一句自我介绍
    RCLCPP_INFO(node->get_logger(),"node_01节点已经启动");
    // 运行节点并检测退出信号
    spin(node);
    // 停止运行
    shutdown();
    return 0;
}