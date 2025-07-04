/**
 * @file entity_state.cpp
 *
 * @brief Entity state data structure
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2021
 */

#include <cmath>
#include <iomanip>
#include "travesim_adapters/data/entity_state.hpp"
#include "travesim_adapters/data/data_common.hpp"

namespace travesim {
/*****************************************
 * Vector2D Related
 *****************************************/

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

void Vector2D::rotate(double theta) {
    double old_x = this->x, old_y = this->y;

    this->x = cos(theta)*old_x + sin(theta)*old_y;
    this->y = -sin(theta)*old_x + cos(theta)*old_y;
}

std::ostream& operator <<(std::ostream& output, const Vector2D& vector_2d) {
    output << std::fixed << std::setprecision(PRINTING_DECIMAL_PRECISION);

    output << "X: " << std::setw(PRINTING_MIN_WIDTH) << vector_2d.x << " | ";
    output << "Y: " << std::setw(PRINTING_MIN_WIDTH) << vector_2d.y;

    return output;
}

/*****************************************
 * EntityState Related
 *****************************************/

EntityState::EntityState() : EntityState(Vector2D(), 0.0, Vector2D(), 0.0) {
}

EntityState::EntityState(Vector2D position, double angular_position, Vector2D velocity, double angular_velocity) {
    this->position = position;
    this->angular_position = angular_position;
    this->velocity = velocity;
    this->angular_velocity = angular_velocity;
}

std::ostream& operator <<(std::ostream& output, const EntityState& entity_state) {
    output << std::fixed << std::setprecision(PRINTING_DECIMAL_PRECISION);

    output << "POSITION: ";
    output << entity_state.position << " | ";
    output << "THETA: "<< std::setw(PRINTING_MIN_WIDTH) << entity_state.angular_position << std::endl;

    output << "VELOCITY: ";
    output << entity_state.velocity << " | ";
    output << "THETA: "<< std::setw(PRINTING_MIN_WIDTH) << entity_state.angular_velocity << std::endl;

    return output;
}
}
