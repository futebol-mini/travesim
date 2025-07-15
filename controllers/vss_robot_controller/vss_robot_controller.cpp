/**
 * @file vss_robot_controller.cpp
 *
 * @author Felipe Gomes de Melo <felipegmelo.42@gmail.com>
 *
 * @brief
 *
 * @date 07/2025
 *
 * @copyright MIT License - Copyright (c) 2025 Futebol Mini
 */

#include <webots/Robot.hpp>
#include <webots/Receiver.hpp>
#include <webots/Motor.hpp>
#include <string>
#include <memory>
#include <algorithm> // Required for std::transform
#include <cctype>    // Required for std::tolower
#include <cmath>

#include "travesim_webots/message.hpp"

#define MAX_SPEED 68.0

inline double sign(double in) {
    return (std::signbit(in) ? -1.0 : 1.0);
}

inline double clip(double in) {
    return std::min(std::abs(in), MAX_SPEED)*sign(in);
}

int main(int argc, char** argv) {
    std::string team_name(argv[1]);
    uint32_t robot_number = std::stoi(argv[2]);

    std::transform(team_name.begin(), team_name.end(), team_name.begin(),
                   [](u_char c)
    {
        return std::tolower(c);
    });

    // create the Robot instance.
    auto robot = std::make_unique<webots::Robot>();

    // get the time step of the current world.
    int timeStep = (int) robot->getBasicTimeStep();

    const size_t robots_per_team = 3;

    webots::Receiver* receiver = robot->getReceiver("robot_receiver");

    if (!receiver){
        std::exit(6);
    }

    if (team_name.compare("yellow")){
        receiver->setChannel(1);
    } else if (team_name.compare("blue")) {
        receiver->setChannel(0);
    } else {
        std::cerr << "Invalid team name! Got: '"<< team_name << "'" << std::endl;
    }

    receiver->enable(1);

    webots::Motor* left_motor = robot->getMotor("left_motor");
    webots::Motor* right_motor = robot->getMotor("right_motor");

    // Configure motors for speed control
    left_motor->setPosition(std::numeric_limits<double>::infinity());
    right_motor->setPosition(std::numeric_limits<double>::infinity());

    left_motor->setVelocity(0);
    right_motor->setVelocity(0);

    // Main loop:
    // - perform simulation steps until Webots is stopping the controller
    while (robot->step(timeStep) != -1){
        if (receiver->getQueueLength() == 0){
            continue;
        }

        auto message = *(travesim::webots_adapter::message_t<robots_per_team>*) receiver->getData();
        receiver->nextPacket();

        left_motor->setVelocity(clip(message.left_speed[robot_number]));
        right_motor->setVelocity(clip(message.right_speed[robot_number]));
    }

    // Enter here exit cleanup code.
    return 0;
}
