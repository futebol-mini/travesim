/**
 * @file sender.cpp
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

#include <iostream>
#include <string>
#include <exception>
#include <boost/asio.hpp>

#include "travesim_adapters/udp/sender.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define NO_FLAGS 0U

/*****************************************
 * Class Methods Bodies Definitions
 *****************************************/

namespace travesim {
namespace udp {
Sender::Sender(std::string receiver_address, short receiver_port) {
    this->set_receiver_endpoint(receiver_address, receiver_port);

    this->socket = new boost::asio::ip::udp::socket(this->io_context);
    this->socket->open(this->endpoint.protocol());
};

Sender::~Sender() {
    this->socket->close();

    delete this->socket;
};

size_t Sender::send(const char* buffer, const size_t buffer_size) {
    size_t bytes_sent;
    boost::system::error_code ec;

    bytes_sent = this->socket->send_to(boost::asio::buffer(buffer, buffer_size), this->endpoint, NO_FLAGS, ec);

    switch (ec.value()) {
        case boost::system::errc::success: {
            /**
             * @todo Message logging?
             */
            break;
        }

        default: {
            throw boost::system::system_error(ec);
        }
    }

    return bytes_sent;
};

void Sender::set_receiver_endpoint(const std::string receiver_address, const short receiver_port) {
    const boost::asio::ip::address receiver_boost_addr = boost::asio::ip::address::from_string(receiver_address);

    this->endpoint = boost::asio::ip::udp::endpoint(receiver_boost_addr, receiver_port);
};
}  // namespace udp
}  // namespace travesim
