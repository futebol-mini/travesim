#include <array>
#include "Robot.hpp"

std::array<double, 3> vss::Robot::get_position()
{
    const double *position = this->robot_ptr->getPosition();
    return std::array<double, 3>{position[0], position[1], position[2]};
}