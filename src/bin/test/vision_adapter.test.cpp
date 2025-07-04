/**
 * @file vision_adapter.test.cpp
 * @author Felipe Gomes de Melo <felipe.gomes@thunderatz.org>
 * @brief
 * @date 04/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include <iostream>
#include <string>
#include <google/protobuf/util/json_util.h>
#include <google/protobuf/text_format.h>
#include <ros/ros.h>
#include <ros/console.h>
#include <gazebo_msgs/ModelStates.h>

#include <gtest/gtest.h>

#include "travesim_adapters/udp/multicast_receiver.hpp"
#include "packet.pb.h"

#define BUFFER_SIZE 1024U
#define MAX_RETRIES 5

TEST(vision_adapter, relay_messages)
{
    std::string listen_address_str = "0.0.0.0";

    char data_buff[BUFFER_SIZE];

    uint16_t multicast_port = 10002;
    std::string multicast_address_str = "224.0.0.1";

    travesim::udp::MulticastReceiver my_receiver(multicast_address_str, multicast_port);

    size_t data_size = -1;
    size_t retries = 0;

    bool success = false;

    while (!success && retries < MAX_RETRIES) {
        while (retries < MAX_RETRIES && data_size <= 0) {
            EXPECT_NO_THROW(data_size = my_receiver.receive(data_buff, BUFFER_SIZE));
            retries++;
            ros::Duration(0.5).sleep();
        }

        EXPECT_LT(retries, MAX_RETRIES);
        EXPECT_GT(data_size, 0);

        fira_message::sim_to_ref::Environment env_data;
        env_data.ParseFromString(data_buff);

        std::string parsed_msg;

        google::protobuf::util::JsonPrintOptions options;
        options.add_whitespace = true;
        options.always_print_primitive_fields = true;

        google::protobuf::util::MessageToJsonString(env_data, &parsed_msg, options);

        ROS_INFO_STREAM(parsed_msg);

        success = env_data.has_frame();
        data_size = 0;
    }

    EXPECT_EQ(success, true);
}

// Run all the tests that were declared with TEST()
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    ros::init(argc, argv, "tester_vision_adapter");
    ros::NodeHandle nh;
    return RUN_ALL_TESTS();
}
