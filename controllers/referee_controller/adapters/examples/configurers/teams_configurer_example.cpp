/**
 * @file teams_configurer_example.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 *
 * @brief Example on how to use the TeamsConfigurer
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include <ros/ros.h>

#include "travesim_adapters/configurers/teams_configurer.hpp"

/*****************************************
 * Main Function
 *****************************************/

int main(int argc, char** argv) {
    ros::init(argc, argv, "teams_configurer_example");
    ros::NodeHandle node_handle;

    travesim::TeamsConfigurer teams_configurer;

    ROS_INFO("Starting...");
    ROS_INFO_STREAM("========== Default Config ==========" << std::endl << teams_configurer);

    while (ros::ok()) {
        if (teams_configurer.get_reset()) {
            ROS_INFO_STREAM("========== Current Config ==========" << std::endl << teams_configurer);

            std::string address = teams_configurer.get_address(travesim::TeamsConfigurer::TeamColor::YELLOW);
        }

        ros::spinOnce();
    }

    return 0;
}
