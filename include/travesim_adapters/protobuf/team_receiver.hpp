/**
 * @file team_receiver.hpp
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @brief Team control data receiver with UDP and protobuf
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include <memory>

#include "travesim_adapters/udp/unicast_receiver.hpp"
#include "travesim_adapters/data/team_command.hpp"
#include "packet.pb.h"

#ifndef __TEAM_RECEIVER_H__
#define __TEAM_RECEIVER_H__

namespace travesim {
namespace proto {
/**
 * @brief Team control data receiver class with UDP and protobuf
 */
class TeamReceiver {
    public:
        /**
         * @brief Construct a new TeamReceiver object
         *
         * @param receiver_address Team control address
         * @param receiver_port Team control port
         * @param is_yellow Wheter to tecontrol team yellow or blue
         * @param force_specific_source Whether to enable source specific or not, default false
         * @param teams_formation Number of robots per team, default is 3
         *
         * @note The unicast addresses must be in the block 127.0.0.0/8, see
         *       [IANA IPv4 Address Space Registry]
         *       (https://www.iana.org/assignments/iana-ipv4-special-registry/iana-ipv4-special-registry.xhtml)
         *       or the [RFC6890](https://tools.ietf.org/html/rfc6890) for more informations.
         */
        TeamReceiver(const std::string receiver_address, const short receiver_port, bool is_yellow,
                     bool force_specific_source = false,
                     TeamsFormation teams_formation = TeamsFormation::THREE_ROBOTS_PER_TEAM);

        /**
         * @brief Receive the command from a team
         *
         * @param p_team_cmd Pointer where to store the team command
         *
         * @return true if a new message was received, false otherwise
         */
        bool receive(TeamCommand* p_team_cmd);

        /**
         * @brief Set the receiver endpoint
         *
         * @param receiver_address Team control address
         * @param receiver_port Team control port
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
         * @brief Update a TeamCommand object from a Packet protobuf message
         *
         * @param p_packet Pointer to the packet message to be converted
         * @param p_team_cmd Pointer where to store the team command
         */
        void packet_pb_msg_to_team_command(fira_message::sim_to_ref::Packet* p_packet, TeamCommand* p_team_cmd);

    private:
        std::unique_ptr<udp::UnicastReceiver> unicast_receiver;  /**< UDP unicast receiver */

        bool is_yellow;  /**< true for yellow, false for blue */

        std::unique_ptr<TeamCommand> last_team_cmd;
};
}  // namespace proto
}  // namespace travesim

#endif // __TEAM_RECEIVER_H__
