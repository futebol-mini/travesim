#include <iostream>
#include <string>

#include "travesim_adapters/udp/unicast_sender.hpp"

#include "travesim_adapters/data/team_command.hpp"
#include "packet.pb.h"

int main(int argc, char** argv) {
    std::string receiver_addr_str = "127.0.0.1";
    uint16_t receiver_port = 20012;
    travesim::udp::UnicastSender sender(receiver_addr_str, receiver_port);

    fira_message::sim_to_ref::Packet packet;
    fira_message::sim_to_ref::Command* command = packet.mutable_cmd()->add_robot_commands();

    command->set_yellowteam(true);
    command->set_id(0);
    command->set_wheel_left(1.0);
    command->set_wheel_right(-1.0);

    boost::asio::io_context io_context;
    boost::asio::steady_timer my_timer(io_context);

    std::string buffer;
    packet.SerializeToString(&buffer);

    uint16_t frame = 0;

    while (sender.send(buffer.c_str(), buffer.length()) > 0){
        frame++;
        std::cout << "Frame: " << frame << std::endl;

        my_timer.expires_after(std::chrono::seconds(1));
        my_timer.wait();
    }
}
