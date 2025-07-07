/**
 * @file team_command.hpp
 *
 * @brief Team command data structure
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 06/2021
 */

#ifndef __TEAM_COMMAND_H__
#define __TEAM_COMMAND_H__

#include <vector>
#include <iostream>
#include <cstdint>

#include "travesim_adapters/data/data_common.hpp"

namespace travesim {
/**
 * @brief Data structure to hold the command for a robot
 *
 */
class RobotCommand {
    public:
        /**
         * @brief Construct a new Robot Command object
         *
         * @param left_speed Command left speed
         * @param right_speed Command right speed
         */
        RobotCommand(double left_speed = 0, double right_speed = 0);

        /**
         * @brief Output stream operator overloading
         *
         */
        friend std::ostream& operator <<(std::ostream& output, const RobotCommand& command);

        /**
         * @brief Public attributes
         *
         */
        double left_speed;
        double right_speed;
};

/**
 * @brief Data structure to hold the command for a team
 *
 */
class TeamCommand {
    public:
        /**
         * @brief Construct a new Team Command object
         *
         * @param teams_formation Number of robots per team, default is 3
         */
        TeamCommand(TeamsFormation teams_formation = TeamsFormation::THREE_ROBOTS_PER_TEAM);

        /**
         * @brief Output stream operator overloading
         *
         */
        friend std::ostream& operator <<(std::ostream& output, const TeamCommand& command);

        /**
         * @brief Public attributes
         *
         */
        uint8_t robots_per_team;

        std::vector<RobotCommand> robot_command;
};
}

#endif // __TEAM_COMMAND_H__
