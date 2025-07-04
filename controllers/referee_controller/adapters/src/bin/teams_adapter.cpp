/**
 * @file teams_adapter.cpp
 *
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @brief Teams commands adapter execution file
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include <ros/ros.h>
#include <ros/console.h>

#include "travesim_adapters/ros/teams_sender.hpp"

#include "travesim_adapters/data/team_command.hpp"
#include "travesim_adapters/protobuf/team_receiver.hpp"

#include "travesim_adapters/configurers/teams_configurer.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "teams_adapter");
    ros::NodeHandle nh;

    travesim::TeamsConfigurer teams_configurer;

    // Get config
    int32_t yellow_port = teams_configurer.get_port(travesim::TeamsConfigurer::TeamColor::YELLOW);
    std::string yellow_address_str = teams_configurer.get_address(travesim::TeamsConfigurer::TeamColor::YELLOW);

    int32_t blue_port = teams_configurer.get_port(travesim::TeamsConfigurer::TeamColor::BLUE);
    std::string blue_address_str = teams_configurer.get_address(travesim::TeamsConfigurer::TeamColor::BLUE);

    bool specific_source = teams_configurer.get_specific_source();

    int robots_per_team;

    ros::param::param<int>("/robots_per_team", robots_per_team, travesim::TeamsFormation::THREE_ROBOTS_PER_TEAM);

    travesim::TeamsFormation teams_formation;

    if (robots_per_team == int(travesim::TeamsFormation::THREE_ROBOTS_PER_TEAM)) {
        teams_formation = travesim::TeamsFormation::THREE_ROBOTS_PER_TEAM;
    } else if (robots_per_team == int(travesim::TeamsFormation::FIVE_ROBOTS_PER_TEAM)) {
        teams_formation = travesim::TeamsFormation::FIVE_ROBOTS_PER_TEAM;
    } else {
        ROS_ERROR_STREAM("Invalid number of robots per team");
        ros::shutdown();
    }

    // Initialize sender, receivers and commands
    travesim::proto::TeamReceiver yellow_receiver(yellow_address_str, yellow_port, true, specific_source,
                                                  teams_formation);
    travesim::proto::TeamReceiver blue_receiver(blue_address_str, blue_port, false, specific_source, teams_formation);

    travesim::ros_side::TeamsSender teams_sender(teams_formation);

    travesim::TeamCommand yellow_command(teams_formation);
    travesim::TeamCommand blue_command(teams_formation);

    // Start
    ROS_INFO_STREAM("Teams adapter config:" << std::endl << teams_configurer);

    while (ros::ok()) {
        if (yellow_receiver.receive(&yellow_command) || blue_receiver.receive(&blue_command)) {
            teams_sender.send(&yellow_command, &blue_command);
        }

        if (teams_configurer.get_reset()) {
            // Get config
            yellow_port = teams_configurer.get_port(travesim::TeamsConfigurer::TeamColor::YELLOW);
            yellow_address_str = teams_configurer.get_address(travesim::TeamsConfigurer::TeamColor::YELLOW);

            blue_port = teams_configurer.get_port(travesim::TeamsConfigurer::TeamColor::BLUE);
            blue_address_str = teams_configurer.get_address(travesim::TeamsConfigurer::TeamColor::BLUE);

            specific_source = teams_configurer.get_specific_source();

            // Reconfigure yellow team
            yellow_receiver.set_receiver_endpoint(yellow_address_str, yellow_port);
            yellow_receiver.force_specific_source(specific_source);
            yellow_receiver.reset();

            // Reconfigure blue team
            blue_receiver.set_receiver_endpoint(blue_address_str, blue_port);
            blue_receiver.force_specific_source(specific_source);
            blue_receiver.reset();

            // Show config
            ROS_INFO_STREAM("Teams adapter config:" << std::endl << teams_configurer);
        }

        ros::spinOnce();
    }
}
