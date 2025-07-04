/**
 * @file sender.hpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 * @author Lucas Schneider <lucas.schneider@thuneratz.org>
 *
 * @brief Send data using UDP
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include <boost/asio.hpp>
#include <string>

#ifndef __SENDER_H__
#define __SENDER_H__

namespace travesim {
namespace udp {
/**
 * @brief Sender class using UDP
 */
class Sender {
    public:
        /**
         * @brief Construct a new Sender object
         *
         * @param receiver_address Address where to send data
         * @param receiver_port Port where to send data
         */
        Sender(const std::string receiver_address, const short receiver_port);

        /**
         * @brief Destroy the Sender object
         */
        virtual ~Sender();

        /**
         * @brief Send data using UDP
         *
         * @param buffer Buffer to be sent
         * @param buffer_size Size of the buffer to be sent
         *
         * @return size_t Number of bytes sent
         */
        size_t send(const char* buffer, const size_t buffer_size);

        /**
         * @brief Set the receiver endpoint object
         *
         * @param receiver_address Address where to send data
         * @param receiver_port Port where to send data
         */
        void set_receiver_endpoint(const std::string receiver_address, const short receiver_port);

    protected:
        boost::asio::ip::udp::socket* socket;    /**< Network socket */
        boost::asio::ip::udp::endpoint endpoint; /**< Multicast address and port pair */

    private:
        boost::asio::io_context io_context;  /**< boost/asio I/O execution context */
};
}  // namespace udp
}  // namespace travesim

#endif // __SENDER_H__
