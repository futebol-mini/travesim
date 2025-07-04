/**
 * @file vision_receiver.hpp
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 * @brief ROS vision receiver class definition
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#ifndef __VISION_RECEIVER_H__
#define __VISION_RECEIVER_H__

#include <ros/ros.h>
#include <ros/console.h>
#include <gazebo_msgs/ModelStates.h>

namespace travesim {
namespace ros_side {
/**
 * @brief Class to receive Gazebo published messages
 *
 */
class VisionReceiver {
    private:
        /**
         * @brief Cache to save the world state
         */
        gazebo_msgs::ModelStates::ConstPtr world_state;

        /**
         * @brief Subscriber for Gazebo model_states topic
         */
        ros::Subscriber subscriber;

        /**
         * @brief Flag to indicate if a message was recieved
         */
        bool received_message;

        /**
         * @brief Callback function for Gazebo subscriber
         *
         * @param msg Received message
         */
        void receive_callback(const gazebo_msgs::ModelStates::ConstPtr& msg);

    public:
        /**
         * @brief Construct a new Vision Receiver object
         *
         * @note Must be called after ros::init()!
         */
        VisionReceiver();

        /**
         * @brief Get last received message
         *
         * @param msg Pointer where to store the message
         *
         * @return true if a new message was received, false otherwise
         */
        bool receive(gazebo_msgs::ModelStates::ConstPtr* msg);
};
}  // ros_side
}  // travesim

#endif // __VISION_RECEIVER_H__
