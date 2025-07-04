#include <array>
#include <cmath>
#include "Robot.hpp"

std::array<double, 3> vss::Robot::get_position()
{
    const double *position = this->robot_ptr->getPosition();
    return std::array<double, 3>{position[0], position[1], position[2]};
}

travesim::Vector2D vss::Robot::get_position2d()
{
    auto position = this->get_position();
    return travesim::Vector2D(position[0], position[1]);
}

double vss::Robot::get_yaw()
{
    const double * rotation_matrix = this->robot_ptr->getOrientation();

    return atan2(rotation_matrix[0], rotation_matrix[3]);

}
