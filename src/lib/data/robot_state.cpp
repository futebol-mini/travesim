/**
 * @file robot_state.cpp
 *
 * @brief Robot state data structure
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2021
 */

#include <iomanip>
#include "travesim_adapters/data/robot_state.hpp"
#include "travesim_adapters/data/data_common.hpp"

namespace travesim {
/*****************************************
 * RobotState Related
 *****************************************/

RobotState::RobotState() : RobotState(Vector2D(), 0, Vector2D(), 0, true, 0) {
}

RobotState::RobotState(Vector2D position, double angular_position, Vector2D velocity, double angular_velocity,
                       bool is_yellow, int id) :
    EntityState(position, angular_position, velocity, angular_velocity) {
    this->is_yellow = is_yellow;
    this->id = id;
}

RobotState::RobotState(EntityState* entity_state, bool is_yellow, int id) :
    EntityState(entity_state->position,
                entity_state->angular_position,
                entity_state->velocity,
                entity_state->angular_velocity) {
    this->is_yellow = is_yellow;
    this->id = id;
}

std::ostream& operator <<(std::ostream& output, const RobotState& robot_state) {
    output << std::fixed << std::setprecision(PRINTING_DECIMAL_PRECISION);

    output << "TEAM YELLOW: " << robot_state.is_yellow << std::endl;
    output << "ROBOT ID: " << robot_state.id << std::endl;

    output << "POSITION: ";
    output << robot_state.position << " | ";
    output << "THETA: "<< std::setw(PRINTING_MIN_WIDTH) << robot_state.angular_position << std::endl;

    output << "VELOCITY: ";
    output << robot_state.velocity << " | ";
    output << "THETA: "<< std::setw(PRINTING_MIN_WIDTH) << robot_state.angular_velocity << std::endl;

    return output;
}
}
