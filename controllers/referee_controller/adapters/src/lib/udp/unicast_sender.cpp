/**
 * @file unicast_sender.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 * @author Lucas Schneider <lucas.schneider@thuneratz.org>
 *
 * @brief Send data using UDP in unicast mode
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include "travesim_adapters/udp/unicast_sender.hpp"

/*****************************************
 * Class Methods Bodies Definitions
 *****************************************/

namespace travesim {
namespace udp {
UnicastSender::UnicastSender(std::string receiver_address, short receiver_port) :
    Sender(receiver_address, receiver_port) {
    this->socket->set_option(boost::asio::ip::unicast::hops(1));
};
}  // namespace udp
}  // namespace travesim
