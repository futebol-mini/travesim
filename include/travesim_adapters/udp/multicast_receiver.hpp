/**
 * @file multicast_receiver.hpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 * @author Lucas Schneider <lucas.schneider@thuneratz.org>
 *
 * @brief Receiver data using UDP in multicast mode
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include "travesim_adapters/udp/receiver.hpp"

#ifndef __MULTICAST_RECEIVER_H__
#define __MULTICAST_RECEIVER_H__

namespace travesim {
namespace udp {
/**
 * @brief Receiver class using UDP in multicast mode
 */
class MulticastReceiver :
    public Receiver {
    public:
        /**
         * @brief Construct a new Multicast Receiver object
         *
         * @param multicast_address Multicas group address
         * @param multicast_port Multicast group port
         * @param receiver_address Receiver address, has a filtering role, setting
         *                         where the data may be received
         *
         * @note The multicast addresses must be in the range 224.0.0.0 through
         *       239.255.255.255, see [IPv4 Multicast Address Space Registry]
         *       (https://www.iana.org/assignments/multicast-addresses/multicast-addresses.xhtml)
         *       or the [RFC1112](https://tools.ietf.org/html/rfc1112) for more informations.
         */
        MulticastReceiver(const std::string multicast_address, const short multicast_port,
                          const std::string receiver_address);

        /**
         * @brief Construct a new Multicast Receiver object
         *
         * @param multicast_address Multicas group address
         * @param multicast_port Multicast group port
         *
         * @note Use multicast address as listen address
         *
         * @note The multicast addresses must be in the range 224.0.0.0 through
         *       239.255.255.255, see [IPv4 Multicast Address Space Registry]
         *       (https://www.iana.org/assignments/multicast-addresses/multicast-addresses.xhtml)
         *       or the [RFC1112](https://tools.ietf.org/html/rfc1112) for more informations.
         */
        MulticastReceiver(const std::string multicast_address, const short multicast_port);

        /**
         * @brief Destroy the Multicast Receiver object
         */
        ~MulticastReceiver();

        /**
         * @brief Set the multicast address
         *
         * @param multicast_address Multicast group address in a string
         *
         * @warning reset() must be called after changing the address
         *
         * @note The multicast addresses must be in the range 224.0.0.0 through
         *       239.255.255.255, see [IPv4 Multicast Address Space Registry]
         *       (https://www.iana.org/assignments/multicast-addresses/multicast-addresses.xhtml)
         *       or the [RFC1112](https://tools.ietf.org/html/rfc1112) for more informations.
         */
        void set_multicast_address(const std::string multicast_address);

    private:
        boost::asio::ip::address multicast_address;

        /**
         * @brief Open the socket with the desired options
         */
        void open_socket();

        /**
         * @brief Close the socket
         */
        void close_socket();
};
}  // namespace udp
}  // namespace travesim

#endif // __MULTICAST_RECEIVER_H__
