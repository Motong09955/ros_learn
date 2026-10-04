#include "rclcpp/rclcpp.hpp"
using namespace rclcpp;
using namespace std;

int main(int argc, char **argv)
{
    // 调用rclcpp的初始化函数
    init(argc, argv);
    // 调用rclcpp的循环运行我们创建的first_node节点
    spin(make_shared<Node>("first_node"));
    return 0;
}
