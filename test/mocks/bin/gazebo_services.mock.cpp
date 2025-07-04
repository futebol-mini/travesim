/**
 * @file gazebo_services.mock.cpp
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 * @brief
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include <ros/ros.h>
#include <ros/console.h>
#include <gazebo_msgs/ModelState.h>
#include <gazebo_msgs/ModelStates.h>
#include <gazebo_msgs/SetModelState.h>
#include <gazebo_msgs/GetModelState.h>

#include "travesim_adapters/data/converter/ros_side.hpp"

#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, gazebo_msgs::ModelState> world_data;

bool set_model_state(gazebo_msgs::SetModelState::Request& req, gazebo_msgs::SetModelState::Response& res) {
    world_data[req.model_state.model_name] = req.model_state;
    res.success = true;
    return true;
}

bool get_model_state(gazebo_msgs::GetModelState::Request& req, gazebo_msgs::GetModelState::Response& res) {
    res.pose = world_data.at(req.model_name).pose;
    res.twist = world_data.at(req.model_name).twist;
    res.success = true;
    return true;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "gazebo_mock");
    ros::NodeHandle nh;

    ros::ServiceServer setter_service = nh.advertiseService("/gazebo/set_model_state", set_model_state);
    ros::ServiceServer getter_service = nh.advertiseService("/gazebo/get_model_state", get_model_state);

    ros::Publisher pub = nh.advertise<gazebo_msgs::ModelStates>("/gazebo/model_states", 1, true);

    gazebo_msgs::ModelStates empty_msg;

    pub.publish(empty_msg);

    ros::spin();

    return 0;
}
