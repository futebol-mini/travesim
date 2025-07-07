// File:          referee_controller.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Supervisor.hpp>
#include <webots/Node.hpp>
#include <webots/Emitter.hpp>
#include <memory>
#include <array>
#include <span>
#include <iostream>
#include <unordered_map>
#include <iomanip>

#include "Robot.hpp"

#include "travesim_webots/message.hpp"

#include "travesim_adapters/protobuf/team_receiver.hpp"
#include "travesim_adapters/protobuf/vision_sender.hpp"
#include "travesim_adapters/data/field_state.hpp"

std::shared_ptr<std::unordered_map<std::string, webots::Node*>> get_robots_references(webots::Field* children) {
    auto entities = std::make_shared<std::unordered_map<std::string, webots::Node*>>();
    auto count = children->getCount();

    for (int i = 0; i < count; i++){
        webots::Node* node = children->getMFNode(i);
        auto* name = node->getField("name");

        if (name){
            (*entities)[name->getSFString()] = node;
        }
    }

    return entities;
}

int main(int argc, char** argv) {
    /**
     * External interfaces definitions
     */

    std::string referee_address_str(argv[1]);
    uint32_t referee_port = std::stoi(argv[2]);

    std::string yellow_address_str(argv[3]);
    uint32_t yellow_port = std::stoi(argv[4]);

    std::string blue_address_str(argv[5]);
    uint32_t blue_port = std::stoi(argv[6]);

    std::string multicast_addr_str(argv[7]);
    uint32_t multicast_port = std::stoi(argv[8]);

    bool specific_source = true;
    travesim::TeamsFormation teams_formation = travesim::THREE_ROBOTS_PER_TEAM;

    std::cout << "Referee addr: " << referee_address_str << std::endl;
    std::cout << "Referee port: " << referee_port << std::endl;

    std::cout << "Yellow addr: " << yellow_address_str << std::endl;
    std::cout << "Yellow port: " << yellow_port << std::endl;

    std::cout << "Blue addr: " << blue_address_str << std::endl;
    std::cout << "Blue port: " << blue_port << std::endl;

    std::cout << "Vision addr: " << multicast_addr_str << std::endl;
    std::cout << "Vision port: " << multicast_port << std::endl;

    travesim::proto::VisionSender vision_sender(multicast_addr_str, multicast_port);
    travesim::FieldState field_state(teams_formation);

    travesim::proto::TeamReceiver yellow_receiver(yellow_address_str,
                                                  yellow_port,
                                                  true,
                                                  specific_source,
                                                  teams_formation);

    travesim::TeamCommand yellow_command(teams_formation);

    travesim::proto::TeamReceiver blue_receiver(blue_address_str,
                                                blue_port,
                                                true,
                                                specific_source,
                                                teams_formation);

    travesim::TeamCommand blue_command(teams_formation);

    /**
     * Webots interfaces definitions
     */

    auto referee = std::make_unique<webots::Supervisor>();

    auto time_step = (uint16_t) referee->getBasicTimeStep();

    webots::Field* children = referee->getRoot()->getField("children");

    auto robots = get_robots_references(children);

    webots::Emitter* yellow_team_emitter = referee->getEmitter("yellow_team");
    webots::Emitter* blue_team_emitter = referee->getEmitter("blue_team");

    yellow_team_emitter->setChannel(0);
    blue_team_emitter->setChannel(1);

    /**
     * Loop preparation
     */

    uint32_t frame = 0;

    auto yellow_robot = travesim::webots_adapter::Robot(robots->at("YellowRobot0"));

    while (referee->step(time_step) != -1){
        field_state.yellow_team[0].position = yellow_robot.get_position2d();
        field_state.yellow_team[0].angular_position = yellow_robot.get_yaw();

        vision_sender.send(&field_state);

        std::cout << "Angular position: " << yellow_robot.get_yaw() / 3.1416 * 180 << std::endl;

        yellow_receiver.receive(&yellow_command);

        frame++;

        travesim::webots_adapter::message_t message;

        message.frame = frame;
        message.left_speed = yellow_command.robot_command[0].left_speed;
        message.right_speed = yellow_command.robot_command[0].right_speed;

        yellow_team_emitter->send(&message, sizeof(message));
    }

    return 0;
}
