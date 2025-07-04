/**
 * @file vision_receiver.test.cpp
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 * @brief Tests for vision_receiver.cpp
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 * @see VisionReceiver
 */

#include <ros/ros.h>
#include <ros/console.h>
#include <gtest/gtest.h>

#include <gazebo_msgs/ModelStates.h>
#include <gazebo_msgs/SetModelState.h>
#include <gazebo_msgs/GetModelState.h>

#include "travesim_adapters/ros/replacer_sender.hpp"

TEST(replacer_sender, msg_received)
{
    ros::NodeHandle _nh;
    ros::topic::waitForMessage<gazebo_msgs::ModelStates>("/gazebo/model_states", _nh);

    travesim::ros_side::ReplacerSender replacer_sender;

    std::vector<gazebo_msgs::ModelState> list_model_states;

    gazebo_msgs::ModelState yellow_robot;
    gazebo_msgs::ModelState blue_robot;

    yellow_robot.model_name = "yellow_team/robot_0";
    yellow_robot.pose.position.x = 1.0;
    yellow_robot.pose.position.y = 2.0;

    blue_robot.model_name = "blue_team/robot_1";
    blue_robot.pose.position.x = -0.5;
    blue_robot.pose.position.y = 1.3;

    list_model_states.push_back(yellow_robot);
    list_model_states.push_back(blue_robot);

    EXPECT_TRUE(replacer_sender.set_models_state(&list_model_states));

    gazebo_msgs::GetModelState get_model_state;
    get_model_state.request.model_name = "yellow_team/robot_0";
    get_model_state.request.relative_entity_name = "world";

    ros::service::call("/gazebo/get_model_state", get_model_state);

    EXPECT_TRUE(get_model_state.response.success);

    EXPECT_DOUBLE_EQ(get_model_state.response.pose.position.x, list_model_states[0].pose.position.x);
    EXPECT_DOUBLE_EQ(get_model_state.response.pose.position.y, list_model_states[0].pose.position.y);

    get_model_state.request.model_name = "blue_team/robot_1";

    ros::service::call("/gazebo/get_model_state", get_model_state);

    EXPECT_TRUE(get_model_state.response.success);

    EXPECT_DOUBLE_EQ(get_model_state.response.pose.position.x, list_model_states[1].pose.position.x);
    EXPECT_DOUBLE_EQ(get_model_state.response.pose.position.y, list_model_states[1].pose.position.y);
}

// Run all the tests that were declared with TEST()
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "tester_replacer_sender");
    ros::NodeHandle nh;
    return RUN_ALL_TESTS();
}
