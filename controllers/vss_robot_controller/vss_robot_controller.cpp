// File:          vss_robot_controller.cpp
// Date:
// Description:
// Author:
// Modifications:

// You may need to add webots include files such as
// <webots/DistanceSensor.hpp>, <webots/Motor.hpp>, etc.
// and/or to add some other includes
#include <webots/Robot.hpp>
#include <webots/Receiver.hpp>
#include <webots/Motor.hpp>
#include <string>
#include <memory>
#include <algorithm> // Required for std::transform
#include <cctype>    // Required for std::tolower

#include "travesim_webots/message.hpp"

#include "travesim_adapters/data/field_state.hpp"

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char** argv) {
    // create the Robot instance.
    auto robot = std::make_unique<webots::Robot>();

    // get the time step of the current world.
    int timeStep = (int) robot->getBasicTimeStep();

    const travesim::TeamsFormation teams_formation = travesim::THREE_ROBOTS_PER_TEAM;
    const size_t robots_per_team = static_cast<size_t>(teams_formation);

    // You should insert a getDevice-like function in order to get the
    // instance of a device of the robot. Something like:
    // Motor *motor = robot->getMotor("motorname");
    // DistanceSensor *ds = robot->getDistanceSensor("dsname");
    // ds->enable(timeStep);

    std::string team_name = argv[1];
    std::transform(team_name.begin(), team_name.end(), team_name.begin(),
                   [](u_char c)
    {
        return std::tolower(c);
    });

    uint32_t robot_number = std::stoi(argv[2]);

    std::cout << "Team name: " << team_name << " Number: " << robot_number << std::endl;

    webots::Receiver* receiver = robot->getReceiver("robot_receiver");

    if (!receiver){
        std::exit(6);
    }

    receiver->setChannel(0);
    receiver->enable(1);

    webots::Motor* left_motor = robot->getMotor("left_motor");
    webots::Motor* right_motor = robot->getMotor("right_motor");

    // Configure motors for speed control
    left_motor->setPosition(std::numeric_limits<double>::infinity());
    right_motor->setPosition(std::numeric_limits<double>::infinity());

    // Main loop:
    // - perform simulation steps until Webots is stopping the controller
    while (robot->step(timeStep) != -1){
        if (receiver->getQueueLength() == 0){
            continue;
        }

        auto message = *(travesim::webots_adapter::message_t<robots_per_team>*) receiver->getData();
        receiver->nextPacket();

        std::cout << "Received frame: " << message.frame << std::endl;
        std::cout << "Received L vel: " << message.left_speed[robot_number] << std::endl;
        std::cout << "Received R vel: " << message.right_speed[robot_number] << std::endl;

        left_motor->setVelocity(message.left_speed[robot_number]);
        right_motor->setVelocity(message.right_speed[robot_number]);
    }

    // Enter here exit cleanup code.
    return 0;
}
