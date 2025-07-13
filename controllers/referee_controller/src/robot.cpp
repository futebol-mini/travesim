/**
 * @file robot.cpp
 *
 * @author Felipe Gomes de Melo <felipegmelo@usp.br>
 *
 * @brief Inteface class that abstracts webots specific methods
 *
 * @date 07/2025
 *
 * @copyright MIT License - Copyright (c) 2025 Futebol Mini
 */

#include <array>
#include <cmath>
#include "travesim_webots/robot.hpp"

namespace travesim::webots_adapter {
std::array<double, 3> Robot::get_position() {
    const double* position = this->robot_ptr->getPosition();
    return std::array<double, 3>{position[0], position[1], position[2]};
}

travesim::Vector2D Robot::get_position2d() {
    const double* position = this->robot_ptr->getPosition();
    return travesim::Vector2D(position[0], position[1]);
}

double Robot::get_yaw() {
    const double* rotation_matrix = this->robot_ptr->getOrientation();
    return atan2(rotation_matrix[3], rotation_matrix[0]);
}

travesim::Vector2D Robot::get_linear_velocity() {
    const double* velocity = this->robot_ptr->getVelocity();
    return travesim::Vector2D(velocity[0], velocity[1]);
}

double Robot::get_angular_velocity() {
    const double* velocity = this->robot_ptr->getVelocity();
    return velocity[5];
}

void Robot::set_position(double x, double y, double z) {
    const double position[] = {x, y, z};
    this->robot_ptr->getField("translation")->setSFVec3f(position);
}

void Robot::set_yaw(double angle) {
    const double rotation[] = {0.0, 0.0, 1.0, angle};
    this->robot_ptr->getField("rotation")->setSFRotation(rotation);
}

void Robot::stop() {
    this->robot_ptr->resetPhysics();
}
}
