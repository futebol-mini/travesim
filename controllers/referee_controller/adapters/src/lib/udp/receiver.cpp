/**
 * @file receiver.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 * @author Lucas Schneider <lucas.schneider@thuneratz.org>
 *
 * @brief Receiver data using UDP
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include <exception>

#include "travesim_adapters/udp/receiver.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define NO_FLAGS 0U

#define INVALID_ENDPOINT boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0)  // 0.0.0.0:0

namespace travesim {
namespace udp {
/*****************************************
 * Public Methods Bodies Definitions
 *****************************************/

Receiver::Receiver(const std::string receiver_address, const short receiver_port) {
    this->set_receiver_endpoint(receiver_address, receiver_port);

    this->force_specific_source(false);

    this->socket = new boost::asio::ip::udp::socket(io_context);
};

Receiver::~Receiver() {
    delete this->socket;
};

size_t Receiver::receive(char* buffer, const size_t buffer_size) {
    size_t bytes_received;
    boost::system::error_code ec;
    boost::asio::ip::udp::endpoint current_endpoint;

    bytes_received =
        this->socket->receive_from(boost::asio::buffer(buffer, buffer_size), current_endpoint, NO_FLAGS, ec);

    this->validate_sender_endpoint(current_endpoint);

    switch (ec.value()) {
        case boost::system::errc::success: {
            /**
             * @todo sender_endpoint loggin?
             */
            break;
        }

        case boost::asio::error::would_block: {
            bytes_received = 0;
            break;
        }

        default: {
            throw boost::system::system_error(ec);
        }
    }

    return bytes_received;
};

size_t Receiver::receive_latest(char* buffer, const size_t buffer_size) {
    size_t bytes_received;
    boost::system::error_code ec;
    boost::asio::ip::udp::endpoint current_endpoint;

    do {
        bytes_received =
            this->socket->receive_from(
                boost::asio::buffer(buffer, buffer_size),
                current_endpoint,
                NO_FLAGS,
                ec);
    } while (this->socket->available() > 0);

    this->validate_sender_endpoint(current_endpoint);

    switch (ec.value()) {
        case boost::system::errc::success: {
            /**
             * @todo sender_endpoint loggin?
             */
            break;
        }

        case boost::asio::error::would_block: {
            bytes_received = 0;
            break;
        }

        default: {
            throw boost::system::system_error(ec);
        }
    }

    return bytes_received;
};

void Receiver::force_specific_source(bool specific_source) {
    this->specific_source = specific_source;
};

void Receiver::set_receiver_endpoint(const std::string receiver_address, const short receiver_port) {
    const boost::asio::ip::address receiver_boost_addr = boost::asio::ip::address::from_string(receiver_address);
    this->receiver_endpoint = boost::asio::ip::udp::endpoint(receiver_boost_addr, receiver_port);
};

void Receiver::reset(void) {
    this->sender_endpoint = INVALID_ENDPOINT;

    this->close_socket();
    this->open_socket();
};

/*****************************************
 * Protected Methods Bodies Definitions
 *****************************************/

void Receiver::close_socket() {
    if (this->socket->is_open()) {
        this->socket->close();
    }
};

/*****************************************
 * Private Methods Bodies Definitions
 *****************************************/

inline void Receiver::validate_sender_endpoint(boost::asio::ip::udp::endpoint current_sender_endpoint) {
    if (this->specific_source) {
        if (this->sender_endpoint == INVALID_ENDPOINT) {
            this->sender_endpoint = current_sender_endpoint;
        } else if (this->sender_endpoint != current_sender_endpoint) {
            if (current_sender_endpoint != INVALID_ENDPOINT) {
                std::string error_msg = "Error in receiver. Any-source not enabled.";
                throw std::runtime_error(error_msg);
            }
        }
    }
};
}  // namespace udp
}  // namespace travesim
