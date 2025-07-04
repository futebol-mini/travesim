/**
 * @file multicast_receiver.cpp
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

#include "travesim_adapters/udp/multicast_receiver.hpp"

namespace travesim {
namespace udp {
/*****************************************
 * Public Methods Bodies Definitions
 *****************************************/

MulticastReceiver::MulticastReceiver(std::string multicast_address, short multicast_port,
                                     std::string receiver_address) : Receiver(receiver_address, multicast_port) {
    this->set_multicast_address(multicast_address);

    this->open_socket();
};

MulticastReceiver::MulticastReceiver(std::string multicast_address, short multicast_port) :
    MulticastReceiver(multicast_address, multicast_port, multicast_address) {
};

MulticastReceiver::~MulticastReceiver() {
    this->close_socket();
};

void MulticastReceiver::set_multicast_address(const std::string multicast_address) {
    const boost::asio::ip::address multicast_boost_addr = boost::asio::ip::address::from_string(multicast_address);
    this->multicast_address = multicast_boost_addr;
};

/*****************************************
 * Protected Methods Bodies Definitions
 *****************************************/

void MulticastReceiver::open_socket() {
    // Create the socket so that multiple may be bound to the same address.
    this->socket->open(this->receiver_endpoint.protocol());

    this->socket->set_option(boost::asio::ip::udp::socket::reuse_address(true));
    this->socket->set_option(boost::asio::ip::multicast::hops(1));

    // Join the multicast group.
    this->socket->set_option(boost::asio::ip::multicast::join_group(this->multicast_address));

    this->socket->bind(this->receiver_endpoint);

    // Use non blocking for syncronous reading
    this->socket->non_blocking(true);
};

void MulticastReceiver::close_socket() {
    if (this->socket->is_open()) {
        this->socket->set_option(boost::asio::ip::multicast::leave_group(this->multicast_address));
        this->socket->close();
    }
};
}  // namespace udp
}  // namespace travesim
