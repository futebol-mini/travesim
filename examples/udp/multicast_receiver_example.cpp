/**
 * @file multicast_receiver_example.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 * @author Lucas Schneider <lucas.schneider@thuneratz.org>
 *
 * @brief Example on how to use the MulticastReceiver
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "boost/bind.hpp"

#include "travesim_adapters/udp/multicast_receiver.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define BUFFER_SIZE 1024U

/*****************************************
 * Main Function
 *****************************************/

int main(int argc, char* argv[]) {
    const std::string listen_address_str = "0.0.0.0";
    const std::string multicast_address_str = "224.0.0.1";
    const short multicast_port = 10002;

    char data_buff[BUFFER_SIZE];

    try {
        boost::asio::io_context io_context;
        boost::asio::steady_timer my_timer(io_context);
        travesim::udp::MulticastReceiver my_receiver(multicast_address_str, multicast_port);

        size_t data_size = 0;

        for (long int i = 0;; i++) {
            data_size = my_receiver.receive(data_buff, BUFFER_SIZE);

            if (data_size > 0) {
                std::string received_msg(data_buff, data_size);
                std::cout << received_msg << std::endl;
            }

            if (i % 100000 == 0) {
                std::cout << "Loop count: " << i << std::endl;
            }

            my_timer.expires_after(std::chrono::milliseconds(200));
            my_timer.wait();
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
