/**
 * @file unicast_receiver.hpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 * @author Lucas Schneider <lucas.schneider@thuneratz.org>
 *
 * @brief Receiver data using UDP in unicast mode
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include "travesim_adapters/udp/receiver.hpp"

#ifndef __UNICAST_RECEIVER_H__
#define __UNICAST_RECEIVER_H__

namespace travesim {
namespace udp {
/**
 * @brief Receiver class using UDP in unicast mode
 */
class UnicastReceiver :
    public Receiver {
    public:
        /**
         * @brief Construct a new Unicast Receiver object
         *
         * @param receiver_address Address where to send data
         * @param receiver_port Port where to send data
         *
         * @note The unicast addresses must be in the block 127.0.0.0/8, see
         *       [IANA IPv4 Address Space Registry]
         *       (https://www.iana.org/assignments/iana-ipv4-special-registry/iana-ipv4-special-registry.xhtml)
         *       or the [RFC6890](https://tools.ietf.org/html/rfc6890) for more informations.
         */
        UnicastReceiver(const std::string receiver_address, const short receiver_port);

        /**
         * @brief Destroy the Unicast Receiver object
         */
        ~UnicastReceiver();

    private:
        /**
         * @brief Open the socket with the desired options
         */
        void open_socket();
};
}  // namespace udp
}  // namespace travesim

#endif // __UNICAST_RECEIVER_H__
