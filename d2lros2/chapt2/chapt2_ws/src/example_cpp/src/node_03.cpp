#include "rclcpp/rclcpp.hpp"
using namespace rclcpp;
using namespace std;

class Node03 : public Node
{

    public:
        Node03(string name) : Node(name)
        {
            RCLCPP_INFO(this->get_logger(),"大家好，我是Node03");
        }

    private:

};

int main(int argc,char **argv)
{
    init(argc,argv);
    auto node = make_shared<Node03>("node_03");
    spin(node);
    shutdown();
    return 0;
}