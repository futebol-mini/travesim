/**
 * @file unicast_receiver.cpp
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

#include "travesim_adapters/udp/unicast_receiver.hpp"

namespace travesim {
namespace udp {
/*****************************************
 * Public Methods Bodies Definitions
 *****************************************/

UnicastReceiver::UnicastReceiver(std::string receiver_address, short receiver_port) : Receiver(receiver_address,
                                                                                               receiver_port) {
    this->open_socket();
};

UnicastReceiver::~UnicastReceiver() {
    this->close_socket();
};

/*****************************************
 * Protected Methods Bodies Definitions
 *****************************************/

void UnicastReceiver::open_socket() {
    this->socket->open(this->receiver_endpoint.protocol());

    this->socket->set_option(boost::asio::ip::unicast::hops(1));
    this->socket->bind(this->receiver_endpoint);

    // Use non blocking for syncronous reading
    this->socket->non_blocking(true);
};
}  // namespace udp
}  // namespace travesim
