/**
 * @file replacer_receiver.hpp
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @brief Replacer receiver with UDP and protobuf
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include <queue>
#include <memory>

#include "travesim_adapters/udp/unicast_receiver.hpp"
#include "travesim_adapters/data/entity_state.hpp"
#include "travesim_adapters/data/robot_state.hpp"
#include "packet.pb.h"

#ifndef __REPLACER_RECEIVER_H__
#define __REPLACER_RECEIVER_H__

namespace travesim {
namespace proto {
/**
 * @brief Replacer receiver class with UDP and protobuf
 */
class ReplacerReceiver {
    public:
        /**
         * @brief Construct a new ReplacerReceiver object
         *
         * @param receiver_address Replacer receiver address
         * @param receiver_port Replacer receiver port
         * @param force_specific_source Whether to enable source specific or not, default false
         *
         * @note The unicast addresses must be in the block 127.0.0.0/8, see
         *       [IANA IPv4 Address Space Registry]
         *       (https://www.iana.org/assignments/iana-ipv4-special-registry/iana-ipv4-special-registry.xhtml)
         *       or the [RFC6890](https://tools.ietf.org/html/rfc6890) for more informations.
         */
        ReplacerReceiver(const std::string receiver_address, const short receiver_port,
                         bool force_specific_source = false);

        /**
         * @brief Receive the replacement commands
         *
         * @param p_replament_queue Pointer to a queue where to store the desired replacements
         *
         * @return true if a new message was received, false otherwise
         */
        bool receive(std::queue<std::shared_ptr<EntityState>>* p_replament_queue);

        /**
         * @brief Set the receiver endpoint
         *
         * @param receiver_address Replacer receiver address
         * @param receiver_port Replacer receiver port
         *
         * @note The unicast addresses must be in the block 127.0.0.0/8, see
         *       [IANA IPv4 Address Space Registry]
         *       (https://www.iana.org/assignments/iana-ipv4-special-registry/iana-ipv4-special-registry.xhtml)
         *       or the [RFC6890](https://tools.ietf.org/html/rfc6890) for more informations.
         */
        void set_receiver_endpoint(const std::string receiver_address, const short receiver_port);

        /**
         * @brief Set wheter to enable any source or source specific multicast.
         *        True for specific source, false for any source, default is false.
         *
         * @param force_specific_source Whether to enable source specific or not.
         */
        void force_specific_source(bool force_specific_source);

        /**
         * @brief Reset the receiver
         */
        void reset(void);

        /**
         * @brief Convert a BallReplacement protobuf message to a EntityState
         *
         * @param p_ball_pb_msg Pointer the ball replacement protobuf message
         *
         * @return Converted EntityState
         */
        EntityState ball_rplcmt_pb_to_entity_state(const fira_message::sim_to_ref::BallReplacement* p_ball_pb_msg);

        /**
         * @brief Convert a RobotReplacement protobuf message to a RobotState
         *
         * @param p_robot_pb_msg Pointer the robot replacement protobuf message
         *
         * @return Converted EntityState
         */
        RobotState robot_rplcmt_pb_to_robot_state(const fira_message::sim_to_ref::RobotReplacement* p_robot_pb_msg);

    private:
        std::unique_ptr<udp::UnicastReceiver> unicast_receiver;  /**< UDP unicast receiver */
};
}  // namespace proto
}  // namespace travesim

#endif // __REPLACER_RECEIVER_H__
