/**
 * @file replacer_sender.cpp
 *
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 *
 * @brief ROS replacer sender for gazebo
 * 
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include <ros/console.h>
#include <std_srvs/Empty.h>

#include <unordered_map>

#include "travesim_adapters/ros/replacer_sender.hpp"

namespace travesim {
namespace ros_side {
ReplacerSender::ReplacerSender() {
    _nh = ros::NodeHandlePtr(new ros::NodeHandle());
    this->reconnect_service_client();
}

void ReplacerSender::reconnect_service_client() {
    /**
     * @brief If the connection dropped, we try to reconnect
     */
    if (!this->gz_service.isValid()) {
        this->gz_service = this->_nh->serviceClient<gazebo_msgs::SetModelState>("/gazebo/set_model_state");
    }
}

bool ReplacerSender::set_model_state(gazebo_msgs::ModelState model_state) {
    static gazebo_msgs::SetModelStateRequest request;
    static gazebo_msgs::SetModelStateResponse response;

    this->reconnect_service_client();
    request.model_state = model_state;

    bool status = this->gz_service.call(request, response);

    if (!(status && response.success)) {
        ROS_ERROR_STREAM("Error while calling set_model_state " << model_state);
        return false;
    }

    return true;
}

bool ReplacerSender::set_models_state(state_vector_t* model_states) {
    for (uint32_t i = 0; i < model_states->size(); i++) {
        if (!this->set_model_state(model_states->at(i))) {
            ROS_ERROR_STREAM("Error while calling set_team_state at i = " << i);
            return false;
        }
    }

    return true;
}

bool ReplacerSender::send_command(simulation_command_t command) {
    static std::unordered_map<simulation_command_t, std::string> topics_table({
                {travesim::ros_side::PAUSE, "/gazebo/pause_physics" },
                {travesim::ros_side::RESUME, "/gazebo/unpause_physics"},
                {travesim::ros_side::RESET_WORLD, "/gazebo/reset_world"},
                {travesim::ros_side::RESET_SIMULATION, "/gazebo/reset_simulation"},
            });

    std_srvs::Empty msg;

    if (topics_table[command] == "") {
        return false;
    } else {
        ros::service::call(topics_table[command], msg);
        return true;
    }
}
}  // namespace ros_side
}  // namespace travesim
