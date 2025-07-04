/**
 * @file vision_sender.hpp
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @brief Vision data sender with UDP and protobuf
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include <memory>

#include "travesim_adapters/udp/multicast_sender.hpp"
#include "travesim_adapters/data/field_state.hpp"
#include "packet.pb.h"

#ifndef __VISION_SENDER_H__
#define __VISION_SENDER_H__

namespace travesim {
namespace proto {
/**
 * @brief Vision sender class with UDP and protobuf
 */
class VisionSender {
    public:
        /**
         * @brief Construct a new Vision Sender object
         *
         * @param multicast_address Vision multicast address
         * @param multicast_port Vision multicast port
         *
         * @note The multicast addresses must be in the range 224.0.0.0 through
         *       239.255.255.255, see multicast [IPv4 Multicast Address Space Registry]
         *       (https://www.iana.org/assignments/multicast-addresses/multicast-addresses.xhtml)
         *       or the [RFC1112](https://tools.ietf.org/html/rfc1112) for more informations.
         */
        VisionSender(const std::string multicast_address, const short multicast_port);

        /**
         * @brief Send vision data with UDP and protobuf
         *
         * @param p_field_state Pointer to field state to be sent
         *
         * @return True if sent data successfully, false otherwise
         */
        bool send(FieldState* p_field_state);

        /**
         * @brief Set the multicast endpoint
         *
         * @param multicast_address Vision multicast address
         * @param multicast_port Vision multicast port
         *
         * @note The multicast addresses must be in the range 224.0.0.0 through
         *       239.255.255.255, see multicast [IPv4 Multicast Address Space Registry]
         *       (https://www.iana.org/assignments/multicast-addresses/multicast-addresses.xhtml)
         *       or the [RFC1112](https://tools.ietf.org/html/rfc1112) for more informations.
         */
        void set_multicast_endpoint(const std::string multicast_address, const short multicast_port);

        /**
         * @brief Convert a FieldState object to a Environment protobuf message object
         *
         * @param p_field_state Pointer to field state to be converted
         *
         * @return fira_message::sim_to_ref::Environment
         */
        static fira_message::sim_to_ref::Environment field_state_to_env_pb_msg(FieldState* p_field_state);

    private:
        std::unique_ptr<udp::MulticastSender> multicast_sender;  /**< Pointer to UDP multicast sender */
};
}  // namespace proto
}  // namespace travesim

#endif // __VISION_SENDER_H__
