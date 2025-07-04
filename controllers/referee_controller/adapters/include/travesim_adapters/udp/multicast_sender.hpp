/**
 * @file multicast_sender.hpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 * @author Lucas Schneider <lucas.schneider@thuneratz.org>
 *
 * @brief Send data using UDP in multicast mode
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include "travesim_adapters/udp/sender.hpp"

#ifndef __MULTICAST_SENDER_H__
#define __MULTICAST_SENDER_H__

namespace travesim {
namespace udp {
/**
 * @brief Sender class using UDP in multicast mode
 */
class MulticastSender :
    public Sender {
    public:
        /**
         * @brief Construct a new Multicast Sender object
         *
         * @param multicast_address Multicas group address
         * @param multicast_port Multicas group port
         *
         * @note The multicast addresses must be in the range 224.0.0.0 through
         *       239.255.255.255, see multicast [IPv4 Multicast Address Space Registry]
         *       (https://www.iana.org/assignments/multicast-addresses/multicast-addresses.xhtml)
         *       or the [RFC1112](https://tools.ietf.org/html/rfc1112) for more informations.
         */
        MulticastSender(const std::string multicast_address, const short multicast_port);
};
}  // namespace udp
}  // namespace travesim

#endif // __MULTICAST_SENDER_H__
