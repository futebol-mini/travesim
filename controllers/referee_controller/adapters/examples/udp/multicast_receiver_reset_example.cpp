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
 * @note This example depends on ROS
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 */

#include <ros/ros.h>

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
    const std::string multicast_address_str = "239.255.0.1";
    const short multicast_port = 30001;

    char data_buff[BUFFER_SIZE];

    ros::init(argc, argv, "reset_example_node", ros::init_options::AnonymousName);
    ros::NodeHandle nh;

    bool reset = false;

    ros::param::set("reset", reset);

    try {
        travesim::udp::MulticastReceiver my_receiver(multicast_address_str, multicast_port);

        my_receiver.force_specific_source(true);

        size_t data_size = 0;

        int counter = 0;

        ros::Rate loop_rate(60);

        while (ros::ok()) {
            data_size = my_receiver.receive(data_buff, BUFFER_SIZE);

            if (data_size > 0) {
                std::string received_msg(data_buff, data_size);
                ROS_INFO_STREAM(received_msg << std::endl);
            }

            if (counter % 100 == 0) {
                ROS_INFO_STREAM("Loop count: " << counter << std::endl);
            }

            ros::param::get("reset", reset);

            if (reset) {
                ROS_INFO_STREAM("Receiver reseted!" << std::endl);
                reset = false;
                ros::param::set("reset", reset);
                my_receiver.reset();
            }

            counter++;

            ros::spinOnce();
            loop_rate.sleep();
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
