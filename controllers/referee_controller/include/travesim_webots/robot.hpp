/**
 * @file robot.hpp
 *
 * @author Felipe Gomes de Melo <felipegmelo@usp.br>
 *
 * @brief Inteface class that abstracts webots specific methods
 *
 * @date 07/2025
 *
 * @copyright MIT License - Copyright (c) 2025 Futebol Mini
 */

#include <webots/Robot.hpp>
#include <webots/Node.hpp>

#include "travesim_adapters/data/entity_state.hpp"

namespace travesim {
namespace webots_adapter {
class Robot {
    public:
        Robot(webots::Node* robot_ptr) : robot_ptr(robot_ptr) { };

        Robot() : robot_ptr(nullptr) { };

        std::array<double, 3> get_position();

        travesim::Vector2D get_position2d();

        travesim::Vector2D get_linear_velocity();

        double get_angular_velocity();

        double get_yaw();

        void set_position(double x, double y, double z);

        void set_yaw(double angle);

        void stop();

    private:
        webots::Node* robot_ptr;
};
}
};
