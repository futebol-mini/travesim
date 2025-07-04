/**
 * @file replacer_receiver.cpp
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @brief Replacer receiver with UDP and protobuf
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include <ros/console.h>

#include "travesim_adapters/protobuf/replacer_receiver.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define BUFFER_SIZE 1024U

/*****************************************
 * Public Methods Bodies Definitions
 *****************************************/

namespace travesim {
namespace proto {
ReplacerReceiver::ReplacerReceiver(const std::string receiver_address, const short receiver_port,
                                   bool force_specific_source) {
    this->unicast_receiver =
        std::unique_ptr<udp::UnicastReceiver>(new udp::UnicastReceiver(receiver_address, receiver_port));
    this->unicast_receiver->force_specific_source(force_specific_source);
}

bool ReplacerReceiver::receive(std::queue<std::shared_ptr<EntityState>>* p_replament_queue) {
    char buffer[BUFFER_SIZE];

    size_t data_size = 0;

    try {
        data_size = this->unicast_receiver->receive(buffer, BUFFER_SIZE);
    } catch (std::exception& e) {
        ROS_ERROR_STREAM("Replacer receiver: " << e.what());

        return false;
    }

    if (data_size > 0) {
        fira_message::sim_to_ref::Packet packet_data;
        packet_data.ParseFromArray(buffer, BUFFER_SIZE);

        if (packet_data.has_replace()) {
            for (const auto& robot_replacement : packet_data.replace().robots()) {
                RobotState robot_state = this->robot_rplcmt_pb_to_robot_state(&robot_replacement);
                p_replament_queue->push(std::make_shared<RobotState>(robot_state));
            }

            if (packet_data.replace().has_ball()) {
                const fira_message::sim_to_ref::BallReplacement ball = packet_data.replace().ball();
                EntityState ball_state = this->ball_rplcmt_pb_to_entity_state(&ball);
                p_replament_queue->push(std::make_shared<EntityState>(ball_state));
            }

            return true;
        }
    }

    return false;
}

void ReplacerReceiver::set_receiver_endpoint(const std::string receiver_address, const short receiver_port) {
    this->unicast_receiver->set_receiver_endpoint(receiver_address, receiver_port);
}

void ReplacerReceiver::force_specific_source(bool force_specific_source) {
    this->unicast_receiver->force_specific_source(force_specific_source);
}

void ReplacerReceiver::reset(void) {
    try {
        this->unicast_receiver->reset();
    } catch (std::exception& e) {
        ROS_ERROR_STREAM("Replacer receiver: " << e.what());
    }
}

EntityState ReplacerReceiver::ball_rplcmt_pb_to_entity_state(
    const fira_message::sim_to_ref::BallReplacement* p_ball_pb_msg) {
    EntityState ball_state;

    ball_state.position.x = p_ball_pb_msg->x();
    ball_state.position.y = p_ball_pb_msg->y();
    ball_state.velocity.x = p_ball_pb_msg->vx();
    ball_state.velocity.y = p_ball_pb_msg->vy();

    return ball_state;
}

RobotState ReplacerReceiver::robot_rplcmt_pb_to_robot_state(
    const fira_message::sim_to_ref::RobotReplacement* p_robot_pb_msg) {
    RobotState robot_state;

    robot_state.is_yellow = p_robot_pb_msg->yellowteam();
    robot_state.id = p_robot_pb_msg->position().robot_id();

    robot_state.position.x = p_robot_pb_msg->position().x();
    robot_state.position.y = p_robot_pb_msg->position().y();
    robot_state.angular_position = p_robot_pb_msg->position().orientation();

    robot_state.velocity.x = p_robot_pb_msg->position().vx();
    robot_state.velocity.y = p_robot_pb_msg->position().vy();
    robot_state.angular_velocity = p_robot_pb_msg->position().vorientation();

    return robot_state;
}
}  // namespace proto
}  // namespace travesim
