#include <webots/Robot.hpp>
#include <webots/Node.hpp>

#include "travesim_adapters/data/entity_state.hpp"

namespace travesim {
namespace webots_adapter {
class Robot {
    public:
        Robot(webots::Node* robot_ptr) : robot_ptr(robot_ptr) { };

        std::array<double, 3> get_position();

        travesim::Vector2D get_position2d();

        double get_yaw();

    private:
        webots::Node* robot_ptr;
};
}
};
