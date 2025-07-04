/**
 * @file vision_receiver_example.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 * @author Lucas Schneider <lucas.schneider@thuneratz.org>
 * @author Felipe Gomes de Melo <felipe.gomes@thuneratz.org>
 *
 * @brief Example to read data published from vision adapter
 *
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include <iostream>
#include <string>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/text_format.h>

#include "packet.pb.h"
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
        travesim::udp::MulticastReceiver my_receiver(multicast_address_str, multicast_port);

        size_t data_size = 0;

        for (long int i = 0;; i++) {
            data_size = my_receiver.receive(data_buff, BUFFER_SIZE);

            if (data_size > 0) {
                fira_message::sim_to_ref::Environment env_data;
                env_data.ParseFromString(data_buff);

                std::string parsed_msg;

                google::protobuf::util::JsonPrintOptions options;
                options.add_whitespace = true;
                options.always_print_primitive_fields = true;

                google::protobuf::util::MessageToJsonString(env_data, &parsed_msg, options);

                std::cout << parsed_msg << std::endl;
            }

            if (i % 100000 == 0) {
                std::cout << "Loop count: " << i << std::endl;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
