/**
 * @file replacer_adapter.cpp
 *
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @brief Replacer adapter execution file
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include <queue>
#include <memory>

#include <ros/ros.h>
#include <ros/console.h>
#include <gazebo_msgs/ModelStates.h>

#include "travesim_adapters/ros/replacer_sender.hpp"
#include "travesim_adapters/protobuf/replacer_receiver.hpp"
#include "travesim_adapters/data/converter/ros_side.hpp"
#include "travesim_adapters/configurers/replacer_configurer.hpp"

int main(int argc, char** argv) {
    ros::init(argc, argv, "replacer_adapter");
    ros::NodeHandle nh;

    // Get config
    travesim::ReplacerConfigurer replacer_configurer;

    int32_t receiver_port = replacer_configurer.get_port();
    std::string receiver_address = replacer_configurer.get_address();

    bool specific_source = replacer_configurer.get_specific_source();

    // Initialize sender, receivers and commands
    travesim::ros_side::ReplacerSender replacer_sender;
    travesim::proto::ReplacerReceiver replacer_receiver(receiver_address, receiver_port, specific_source);

    // Define data structures
    travesim::ros_side::state_vector_t model_state_vector;
    std::queue<std::shared_ptr<travesim::EntityState>> states_queue;

    // Start
    ROS_INFO_STREAM("Replacer adapter config:" << std::endl << replacer_configurer);

    while (ros::ok()) {
        bool received_new_msg = replacer_receiver.receive(&states_queue);

        if (received_new_msg) {
            replacer_sender.send_command(travesim::ros_side::PAUSE);

            while (!states_queue.empty()) {
                std::shared_ptr<travesim::RobotState> state = std::dynamic_pointer_cast<travesim::RobotState>(
                    states_queue.front());

                gazebo_msgs::ModelState gazebo_state_msg;

                if (state != nullptr) {
                    gazebo_state_msg = travesim::converter::RobotState_to_ModelState(state.get());
                } else {
                    gazebo_state_msg = travesim::converter::EntityState_to_ModelState(states_queue.front().get());
                }

                model_state_vector.push_back(gazebo_state_msg);

                states_queue.pop();
            }

            replacer_sender.set_models_state(&model_state_vector);

            replacer_sender.send_command(travesim::ros_side::RESUME);

            model_state_vector.clear();
        }

        if (replacer_configurer.get_reset()) {
            // Get config
            receiver_port = replacer_configurer.get_port();
            receiver_address = replacer_configurer.get_address();

            specific_source = replacer_configurer.get_specific_source();

            // Reconfigure receiver
            replacer_receiver.set_receiver_endpoint(receiver_address, receiver_port);
            replacer_receiver.force_specific_source(specific_source);
            replacer_receiver.reset();

            // Show config
            ROS_INFO_STREAM("Replacer adapter config:" << std::endl << replacer_configurer);
        }

        ros::spinOnce();
    }
}
