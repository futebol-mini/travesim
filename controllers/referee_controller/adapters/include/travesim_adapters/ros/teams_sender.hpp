/**
 * @file teams_sender.hpp
 *
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @brief ROS teams commands sender class definition
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#ifndef __TEAMS_SENDER_H__
#define __TEAMS_SENDER_H__

#include <ros/ros.h>
#include <ros/console.h>

#include "travesim_adapters/data/team_command.hpp"
#include "travesim_adapters/data/data_common.hpp"

#include <vector>
#include <iostream>

namespace travesim {
namespace ros_side {
/**
 * @brief Helper struct to group same robot command topics
 */
typedef struct {
    ros::Publisher left;
    ros::Publisher right;
} robot_command_pub_t;

class TeamsSender {
    private:
        /**
         * @brief Yellow team ROS publishers
         *
         */
        std::vector<robot_command_pub_t> yellow_pubs;

        /**
         * @brief Blue team ROS publishers
         *
         */
        std::vector<robot_command_pub_t> blue_pubs;

        uint8_t robots_per_team;

    public:
        /**
         * @brief Construct a new Teams Sender object
         *
         * @param teams_formation Number of robots per team, default is 3
         */
        TeamsSender(TeamsFormation teams_formation = TeamsFormation::THREE_ROBOTS_PER_TEAM);

        /**
         * @brief Send the stored commands to Gazebo controllers
         *
         */
        void send(TeamCommand* yellow_team_command, TeamCommand* blue_team_command);
};
}  // ros_side
}  // travesim

#endif // __TEAMS_SENDER_H__
