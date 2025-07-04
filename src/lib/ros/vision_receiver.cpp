/**
 * @file vision_receiver.cpp
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 * @brief ROS vision receiver class definition
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include <ros/console.h>
#include <gazebo_msgs/ModelStates.h>
#include "travesim_adapters/ros/vision_receiver.hpp"

namespace travesim {
namespace ros_side {
VisionReceiver::VisionReceiver() {
    this->received_message = false;

    ros::NodeHandle _nh;
    this->subscriber = _nh.subscribe("/gazebo/model_states", 2, &VisionReceiver::receive_callback, this);
}

bool VisionReceiver::receive(gazebo_msgs::ModelStates::ConstPtr* msg) {
    if (this->received_message) {
        *msg = this->world_state;
        this->received_message = false;

        return true;
    }

    return false;
}

void VisionReceiver::receive_callback(const gazebo_msgs::ModelStates::ConstPtr& msg) {
    this->received_message = true;
    this->world_state = msg;
}
}  // namespace ros_side
}  // namespace travesim
