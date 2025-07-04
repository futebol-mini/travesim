/**
 * @file multicast_sender.cpp
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

#include "travesim_adapters/udp/multicast_sender.hpp"

/*****************************************
 * Class Methods Bodies Definitions
 *****************************************/

namespace travesim {
namespace udp {
MulticastSender::MulticastSender(std::string multicast_address, short multicast_port) :
    Sender(multicast_address, multicast_port) {
    this->socket->set_option(boost::asio::ip::multicast::hops(1));
};
}  // namespace udp
}  // namespace travesim
