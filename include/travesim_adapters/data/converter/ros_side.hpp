/**
 * @file ros_side.hpp
 *
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @brief Collection of data converters between ROS and local formats
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include <iostream>

#include <geometry_msgs/Point.h>
#include <geometry_msgs/Vector3.h>
#include <gazebo_msgs/ModelState.h>
#include <gazebo_msgs/ModelStates.h>

#include "travesim_adapters/data/data_common.hpp"
#include "travesim_adapters/data/robot_state.hpp"
#include "travesim_adapters/data/entity_state.hpp"
#include "travesim_adapters/data/field_state.hpp"

#define DEFAULT_Z_VALUE_BALL 0.032
#define DEFAULT_Z_VALUE_ROBOT 0.012

#define ROBOT_NAME(color, num) color "_team/robot_" + std::to_string(num)

#define BALL_NAME "vss_ball"

#define DEFAULT_ENTITY_NAME BALL_NAME
#define DEFAULT_REFERENCE_FRAME "world"

namespace travesim {
namespace converter {
/**
 * @brief Function to convert geometry_msgs::Point to travesim::Vector2D
 *
 * @param point Data to be converted
 * @return travesim::Vector2D Converted data
 */
travesim::Vector2D Point_to_Vector2D(geometry_msgs::Point* point);

/**
 * @brief Function to convert geometry_msgs::Vector3 to travesim::Vector2D
 *
 * @param vector3 Data to be converted
 * @return travesim::Vector2D Converted data
 */
travesim::Vector2D Vector3_to_Vector2D(geometry_msgs::Vector3* vector3);

/**
 * @brief Function to convert gazebo_msgs::ModelState to travesim::EntityState
 *
 * @param model_state Data to be converted
 * @return travesim::EntityState Converted data
 */
travesim::EntityState ModelState_to_EntityState(gazebo_msgs::ModelState* model_state);

/**
 * @brief Function to convert gazebo_msgs::ModelState to travesim::RobotState
 *
 * @param model_state Data to be converted
 * @param is_yellow True if the robot is from the yellow team, false otherwise
 * @param id Id number of the robot
 * @return travesim::RobotState Converte data
 */
travesim::RobotState ModelState_to_RobotState(gazebo_msgs::ModelState* model_state, bool is_yellow = true, int id = 0);

/**
 * @brief Function to convert travesim::Vector2D to geometry_msgs::Vector3
 *
 * @param vector2d Data to be converted
 * @return geometry_msgs::Vector3 Converted data
 */
geometry_msgs::Vector3 Vector2D_to_Vector3(Vector2D* vector2d);

/**
 * @brief Function to convert travesim::Vector2D to geometry_msgs::Point
 *
 * @param vector2d Data to be converted
 * @return geometry_msgs::Point Converted data
 */
geometry_msgs::Point Vector2D_to_Point(Vector2D* vector2d, double z = DEFAULT_Z_VALUE_BALL);

/**
 * @brief Function to convert travesim::EntityState to gazebo_msgs::ModelState
 *
 * @param entity_state Data to be converted
 * @return gazebo_msgs::ModelState Converted data
 */
gazebo_msgs::ModelState EntityState_to_ModelState(EntityState* entity_state, double z = DEFAULT_Z_VALUE_BALL);

/**
 * @brief Function to convert travesim::RobotState to gazebo_msgs::ModelState
 *
 * @param entity_state Data to be converted
 * @return gazebo_msgs::ModelState Converted data
 */
gazebo_msgs::ModelState RobotState_to_ModelState(RobotState* robot_state, double z = DEFAULT_Z_VALUE_ROBOT);

/**
 * @brief Function to convert gazebo_msgs::ModelStates to travesim::FieldState
 *
 * @param model_states Data to be converted
 * @param teams_formation Number of robots per team
 *
 * @return travesim::FieldState Converted data
 */
travesim::FieldState ModelStates_to_FieldState(gazebo_msgs::ModelStates::ConstPtr model_states,
                                               TeamsFormation                     teams_formation);
}  // namespace converter
}  // namespace travesim

#endif // __CONVERTER_H__
