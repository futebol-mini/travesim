/**
 * @file converter.test.cpp
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 * @brief
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include <ros/ros.h>
#include <ros/console.h>
#include <gtest/gtest.h>
#include <gazebo_msgs/ModelState.h>
#include <geometry_msgs/Vector3.h>
#include <iostream>

#include "travesim_adapters/data/converter/ros_side.hpp"
#include "travesim_adapters/data/robot_state.hpp"
#include "travesim_adapters/ros/vision_receiver.hpp"

TEST(vector2d_to_vector3, convert_from_vector2d)
{
    travesim::Vector2D vector2d(2, 4);

    geometry_msgs::Vector3 vector3 = travesim::converter::Vector2D_to_Vector3(&vector2d);

    EXPECT_DOUBLE_EQ(vector3.x, 2);
    EXPECT_DOUBLE_EQ(vector3.y, 4);
}

TEST(vector2d_to_vector3, convert_from_vector3)
{
    geometry_msgs::Vector3 vector3;

    vector3.x = 3;
    vector3.y = -7;

    travesim::Vector2D vector2d = travesim::converter::Vector3_to_Vector2D(&vector3);

    EXPECT_DOUBLE_EQ(vector2d.x, 3);
    EXPECT_DOUBLE_EQ(vector2d.y, -7);
}

TEST(robot_state_to_model_state, model_name)
{
    travesim::RobotState robot_state;

    EXPECT_EQ(travesim::converter::RobotState_to_ModelState(&robot_state).model_name, "yellow_team/robot_0");

    robot_state.id = 2;

    EXPECT_EQ(travesim::converter::RobotState_to_ModelState(&robot_state).model_name, "yellow_team/robot_2");

    robot_state.is_yellow = false;
    robot_state.id = 0;

    EXPECT_EQ(travesim::converter::RobotState_to_ModelState(&robot_state).model_name,
              "blue_team/robot_0");

    robot_state.id = 1;

    EXPECT_EQ(travesim::converter::RobotState_to_ModelState(&robot_state).model_name,
              "blue_team/robot_1");
}

TEST(robot_state_to_model_state, angle_conversion)
{
    travesim::RobotState robot_state;
    robot_state.angular_position = -M_PI/3;

    gazebo_msgs::ModelState model_state = travesim::converter::RobotState_to_ModelState(&robot_state);

    EXPECT_DOUBLE_EQ(travesim::converter::ModelState_to_RobotState(&model_state).angular_position,
                     robot_state.angular_position);
}

// Run all the tests that were declared with TEST()
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    // ros::init(argc, argv, "tester");
    // ros::NodeHandle nh;
    return RUN_ALL_TESTS();
}
