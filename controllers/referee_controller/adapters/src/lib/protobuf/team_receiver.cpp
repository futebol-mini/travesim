/**
 * @file team_receiver.cpp
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @brief Team control data receiver with UDP and protobuf
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include <ros/console.h>

#include "travesim_adapters/protobuf/team_receiver.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define BUFFER_SIZE 1024U

/*****************************************
 * Public Methods Bodies Definitions
 *****************************************/

namespace travesim {
namespace proto {
TeamReceiver::TeamReceiver(const std::string receiver_address, const short receiver_port, bool is_yellow,
                           bool force_specific_source, TeamsFormation teams_formation) {
    this->unicast_receiver =
        std::unique_ptr<udp::UnicastReceiver>(new udp::UnicastReceiver(receiver_address, receiver_port));
    this->unicast_receiver->force_specific_source(force_specific_source);

    this->is_yellow = is_yellow;

    this->last_team_cmd = std::unique_ptr<TeamCommand>(new TeamCommand(teams_formation));
}

bool TeamReceiver::receive(TeamCommand* p_team_cmd) {
    char buffer[BUFFER_SIZE];

    size_t data_size = 0;

    try {
        data_size = this->unicast_receiver->receive_latest(buffer, BUFFER_SIZE);
    } catch (std::exception& e) {
        ROS_ERROR_STREAM((this->is_yellow ? "Yellow" : "Blue") << " team receiver: " << e.what());

        return false;
    }

    if (data_size > 0) {
        fira_message::sim_to_ref::Packet packet_data;
        packet_data.ParseFromArray(buffer, BUFFER_SIZE);

        if (packet_data.has_cmd()) {
            this->packet_pb_msg_to_team_command(&packet_data, p_team_cmd);

            *last_team_cmd = *p_team_cmd;

            return true;
        } else {
            *p_team_cmd = *last_team_cmd;
        }
    } else {
        *p_team_cmd = *last_team_cmd;
    }

    return false;
}

void TeamReceiver::set_receiver_endpoint(const std::string receiver_address, const short receiver_port) {
    this->unicast_receiver->set_receiver_endpoint(receiver_address,
                                                  receiver_port);
}

void TeamReceiver::force_specific_source(bool force_specific_source) {
    this->unicast_receiver->force_specific_source(force_specific_source);
}

void TeamReceiver::reset(void) {
    try {
        this->unicast_receiver->reset();
    } catch (std::exception& e) {
        ROS_ERROR_STREAM((this->is_yellow ? "Yellow" : "Blue") << " team receiver: " << e.what());
    }
}

void TeamReceiver::packet_pb_msg_to_team_command(fira_message::sim_to_ref::Packet* p_packet, TeamCommand* p_team_cmd) {
    for (const auto& robot_cmd : p_packet->cmd().robot_commands()) {
        if (robot_cmd.yellowteam() == this->is_yellow) {
            int robot_id = robot_cmd.id();

            if ((robot_id < 0) || (robot_id >= p_team_cmd->robots_per_team)) {
                ROS_WARN_STREAM("Error: Invalid robot id in team receiver!\r\nReceived id is " <<
                                robot_id << " and max id is " << p_team_cmd->robots_per_team);
                continue;
            }

            if (isnanf(robot_cmd.wheel_left()) || isnanf(robot_cmd.wheel_right())) {
                ROS_WARN_STREAM("Error: Invalid robot speed in team receiver!");
                continue;
            }

            p_team_cmd->robot_command[robot_id].left_speed = robot_cmd.wheel_left();
            p_team_cmd->robot_command[robot_id].right_speed = robot_cmd.wheel_right();
        } else {
            ROS_WARN("Error: Team %s receiver and command colors don't match!",
                     this->is_yellow ? "yellow" : "blue");
        }
    }
}
}  // namespace proto
}  // namespace travesim
