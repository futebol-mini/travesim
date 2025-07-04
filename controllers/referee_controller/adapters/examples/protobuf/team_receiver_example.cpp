/**
 * @file team_receiver_example.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 * @author Lucas Schneider <lucas.schneider@thuneratz.org>
 * @author Felipe Gomes de Melo <felipe.gomes@thuneratz.org>
 *
 * @brief Example to read data published from a team
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include <iostream>
#include <boost/asio.hpp>

#include "travesim_adapters/protobuf/team_receiver.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define BUFFER_SIZE 1024U
#define CLEAR_TERMINAL "\033[2J\033[H"

/*****************************************
 * Main Function
 *****************************************/

int main(int argc, char* argv[]) {
    const std::string receiver_address = "127.0.0.1";
    const short receiver_port = 20011;

    travesim::TeamCommand team_yellow_cmd;

    try {
        boost::asio::io_context io_context;
        boost::asio::steady_timer my_timer(io_context);
        travesim::proto::TeamReceiver yellow_receiver(receiver_address, receiver_port, true);

        while (true) {
            bool received_new_msg = yellow_receiver.receive(&team_yellow_cmd);

            if (received_new_msg) {
                std::cout << CLEAR_TERMINAL << team_yellow_cmd;
            }

            my_timer.expires_after(std::chrono::milliseconds(1));
            my_timer.wait();
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
