/**
 * @file unicast_receiver_example.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 * @author Lucas Schneider <lucas.schneider@thuneratz.org>
 *
 * @brief Example on how to use the UnicastReceiver
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include <iostream>

#include "travesim_adapters/udp/unicast_receiver.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define BUFFER_SIZE 1024U

/*****************************************
 * Main Function
 *****************************************/

int main(int argc, char* argv[]) {
    const std::string unicast_address_str = "127.0.0.1";
    const short unicast_port = 30001;

    char data_buff[BUFFER_SIZE];

    try {
        boost::asio::io_context io_context;
        boost::asio::steady_timer my_timer(io_context);
        travesim::udp::UnicastReceiver my_receiver(unicast_address_str, unicast_port);

        my_receiver.force_specific_source(true);

        size_t data_size = 0;

        for (long int i = 0;; i++) {
            data_size = my_receiver.receive(data_buff, BUFFER_SIZE);

            if (data_size > 0) {
                std::string received_msg(data_buff, data_size);
                std::cout << received_msg << std::endl;
            }

            my_timer.expires_after(std::chrono::milliseconds(200));
            my_timer.wait();
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
