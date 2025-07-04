/**
 * @file replacer_sender.hpp
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 * @brief
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#ifndef __REPLACER_SENDER_H__
#define __REPLACER_SENDER_H__

#include <ros/ros.h>
#include <gazebo_msgs/SetModelState.h>

namespace travesim {
namespace ros_side {
/**
 * @brief All possible commands to send to Gazebo
 *
 * @see send_command
 */
enum simulation_command_t {
    PAUSE,
    RESUME,
    RESET_WORLD,
    RESET_SIMULATION
};

/**
 * @brief Helper type to set the states of multiple entites at once
 *
 */
typedef std::vector<gazebo_msgs::ModelState> state_vector_t;

class ReplacerSender {
    private:
        ros::NodeHandlePtr _nh;

        ros::ServiceClient gz_service;

    public:
        /**
         * @brief Construct a new Replacer Sender object
         *
         */
        ReplacerSender();

        /**
         * @brief Set state of multiple entities
         *
         * @param model_states Vector of states to be set
         *
         * @note The affected entity is infered from the model_name of each ModelState
         *
         * @return true If sucessfull
         * @return false If any error occured
         */
        bool set_models_state(state_vector_t* model_states);

        /**
         * @brief Set the state of one entity
         *
         * @param model_state ModelState to be set
         *
         * @note The affected entity is infered from the model_name of the ModelState
         *
         * @return true If sucessfull
         * @return false If any error occured
         */
        bool set_model_state(gazebo_msgs::ModelState model_state);

        /**
         * @brief Send command to gazebo
         *
         * @param command
         * @return true If sucessfull
         * @return false If any error occured
         */
        bool send_command(simulation_command_t command);

        /**
         * @brief Attempts to reconnect gz_service ServiceClient if connection dropped
         *
         */
        void reconnect_service_client();
};
}  // namespace ros_side
}  // namespace travesim

#endif // __REPLACER_SENDER_H__
