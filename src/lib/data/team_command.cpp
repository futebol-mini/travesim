/**
 * @file team_command.cpp
 *
 * @brief Team command data structure
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 06/2021
 */

#include <iomanip>
#include "travesim_adapters/data/team_command.hpp"

namespace travesim {
/*****************************************
 * RobotCommand Related
 *****************************************/

RobotCommand::RobotCommand(double left_speed, double right_speed) {
    this->left_speed = left_speed;
    this->right_speed = right_speed;
}

std::ostream& operator <<(std::ostream& output, const RobotCommand& command) {
    output << std::fixed << std::setprecision(PRINTING_DECIMAL_PRECISION);

    output << "LEFT SPEED: " << std::setw(PRINTING_MIN_WIDTH) << command.left_speed << std::endl;
    output << "RIGHT SPEED: " << std::setw(PRINTING_MIN_WIDTH) << command.right_speed;

    return output;
}

/*****************************************
 * TeamCommand Related
 *****************************************/

TeamCommand::TeamCommand(TeamsFormation teams_formation) : robots_per_team(teams_formation) {
    this->robot_command = std::vector<RobotCommand>(this->robots_per_team);
}

std::ostream& operator <<(std::ostream& output, const TeamCommand& command) {
    output << std::fixed << std::setprecision(PRINTING_DECIMAL_PRECISION);

    for (int i = 0; i < command.robots_per_team; i++) {
        output << "ROBOT " << i << ":" << std::endl;
        output << command.robot_command[i] << std::endl;
        output << std::endl;
    }

    return output;
}
}
