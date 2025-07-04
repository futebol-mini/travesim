/**
 * @file team_command.cpp
 *
 * @brief Team command data structure
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2021
 */

#include <iomanip>
#include "travesim_adapters/data/field_state.hpp"

namespace travesim {
/*****************************************
 * FieldState Related
 *****************************************/

FieldState::FieldState(TeamsFormation teams_formation) : robots_per_team(teams_formation) {
    this->yellow_team = std::vector<EntityState>(this->robots_per_team);
    this->blue_team = std::vector<EntityState>(this->robots_per_team);
}

std::ostream& operator <<(std::ostream& output, const FieldState& field_state) {
    output << "TIME STEP: " << std::endl;
    output << field_state.time_step << std::endl;

    output << "BALL STATE: " << std::endl;
    output << field_state.ball << std::endl;

    output << "TEAM YELLOW STATE: " << std::endl;

    for (int i = 0; i < field_state.robots_per_team; i++) {
        output << "ROBOT " << i << ":" << std::endl;
        output << field_state.yellow_team[i] << std::endl;
    }

    output << std::endl;

    output << "TEAM BLUE STATE: " << std::endl;

    for (int i = 0; i < field_state.robots_per_team; i++) {
        output << "ROBOT " << i << ":" << std::endl;
        output << field_state.blue_team[i] << std::endl;
    }

    output << std::endl;

    return output;
}
}
