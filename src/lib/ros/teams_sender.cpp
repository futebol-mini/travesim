/**
 * @file teams_sender.cpp
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

#include <ros/ros.h>
#include <std_msgs/Float64.h>

#include "travesim_adapters/ros/teams_sender.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define BUFFER_SIZE 2

/*****************************************
 * Private MAcros
 *****************************************/

#define ROBOT_WHEEL_TOPIC(color, num, side) \
    "/" color "_team/robot_" + std::to_string(num) + "/" side "_controller/command"

/*****************************************
 * Class Definition
 *****************************************/

namespace travesim {
namespace ros_side {
TeamsSender::TeamsSender(TeamsFormation teams_formation) : robots_per_team(teams_formation) {
    ros::NodeHandle nh;

    this->yellow_pubs = std::vector<robot_command_pub_t>(this->robots_per_team);
    this->blue_pubs = std::vector<robot_command_pub_t>(this->robots_per_team);

    for (uint8_t i = 0; i < this->robots_per_team; i++) {
        this->yellow_pubs[i] = {
            .left = nh.advertise<std_msgs::Float64>(ROBOT_WHEEL_TOPIC("yellow", i, "left"), BUFFER_SIZE),
            .right = nh.advertise<std_msgs::Float64>(ROBOT_WHEEL_TOPIC("yellow", i, "right"), BUFFER_SIZE)
        };

        this->blue_pubs[i] = {
            .left = nh.advertise<std_msgs::Float64>(ROBOT_WHEEL_TOPIC("blue", i, "left"), BUFFER_SIZE),
            .right = nh.advertise<std_msgs::Float64>(ROBOT_WHEEL_TOPIC("blue", i, "right"), BUFFER_SIZE)
        };
    }
}

void TeamsSender::send(TeamCommand* yellow_team_command, TeamCommand* blue_team_command) {
    std_msgs::Float64 yellow_left_msg, yellow_right_msg;
    std_msgs::Float64 blue_left_msg, blue_right_msg;

    for (uint8_t i = 0; i < this->robots_per_team; i++) {
        yellow_left_msg.data = yellow_team_command->robot_command[i].left_speed;
        yellow_right_msg.data = yellow_team_command->robot_command[i].right_speed;

        blue_left_msg.data = blue_team_command->robot_command[i].left_speed;
        blue_right_msg.data = blue_team_command->robot_command[i].right_speed;

        this->yellow_pubs[i].left.publish(yellow_left_msg);
        this->yellow_pubs[i].right.publish(yellow_right_msg);

        this->blue_pubs[i].left.publish(blue_left_msg);
        this->blue_pubs[i].right.publish(blue_right_msg);
    }
}
}  // namespace ros_side
}  // namespace travesim
