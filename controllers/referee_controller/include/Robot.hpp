#include <webots/Robot.hpp>
#include <webots/Node.hpp>

namespace vss
{
    class Robot
    {
    public:
        Robot(webots::Node *robot_ptr) : robot_ptr(robot_ptr) {};

        std::array<double, 3> get_position();

    private:
        webots::Node *robot_ptr;
    };
};
