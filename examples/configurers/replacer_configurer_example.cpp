/**
 * @file replacer_configurer_example.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 *
 * @brief Example on how to use the ReplacerConfigurer
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include <ros/ros.h>

#include "travesim_adapters/configurers/replacer_configurer.hpp"

/*****************************************
 * Main Function
 *****************************************/

int main(int argc, char** argv) {
    ros::init(argc, argv, "replacer_configurer_example");
    ros::NodeHandle node_handle;

    travesim::ReplacerConfigurer replacer_configurer;

    ROS_INFO("Starting...");
    ROS_INFO_STREAM("========== Default Config ==========" << std::endl << replacer_configurer);

    while (ros::ok()) {
        if (replacer_configurer.get_reset()) {
            ROS_INFO_STREAM("========== Current Config ==========" << std::endl << replacer_configurer);

            std::string address = replacer_configurer.get_address();
        }

        ros::spinOnce();
    }

    return 0;
}
