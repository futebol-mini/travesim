/**
 * @file vision_adapter.cpp
 *
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @brief Vision adapter executable file
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 * @see VisionReceiver
 * @see VisionSender
 */

#include <ros/ros.h>
#include <ros/console.h>
#include <gazebo_msgs/ModelStates.h>

#include "travesim_adapters/ros/vision_receiver.hpp"
#include "travesim_adapters/data/converter/ros_side.hpp"
#include "travesim_adapters/data/field_state.hpp"
#include "travesim_adapters/data/robot_state.hpp"
#include "travesim_adapters/data/entity_state.hpp"
#include "travesim_adapters/protobuf/vision_sender.hpp"
#include "travesim_adapters/configurers/vision_configurer.hpp"

#include <iostream>

int main(int argc, char** argv) {
    ros::init(argc, argv, "vision_adapter");
    ros::NodeHandle nh;

    travesim::VisionConfigurer vision_configurer;

    int32_t multicast_port = vision_configurer.get_port();
    std::string multicast_address_str = vision_configurer.get_address();

    travesim::ros_side::VisionReceiver vision_receiver;
    travesim::proto::VisionSender vision_sender(multicast_address_str, multicast_port);

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

    travesim::FieldState field_state(teams_formation);
    gazebo_msgs::ModelStates::ConstPtr world_state;

    ROS_INFO_STREAM("Vision adapter config:" << std::endl << vision_configurer);

    field_state.time_step = 0;

    while (ros::ok()) {
        if (vision_receiver.receive(&world_state)) {
            field_state = travesim::converter::ModelStates_to_FieldState(world_state, teams_formation);
            vision_sender.send(&field_state);
            field_state.time_step++;
        }

        if (vision_configurer.get_reset()) {
            multicast_port = vision_configurer.get_port();
            multicast_address_str = vision_configurer.get_address();

            vision_sender.set_multicast_endpoint(multicast_address_str, multicast_port);

            ROS_INFO_STREAM("Vision adapter config:" << std::endl << vision_configurer);
        }

        ros::spinOnce();
    }
}
