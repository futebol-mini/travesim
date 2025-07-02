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
#include <memory>
#include <array>
#include <span>
#include <iostream>
#include <unordered_map>
#include <iomanip>

#include "Robot.hpp"

std::shared_ptr<std::unordered_map<std::string, webots::Node *>> get_robots_references(webots::Field *children){

  auto entities = std::make_shared<std::unordered_map<std::string, webots::Node *>>();
  auto count = children->getCount();

  for (int i = 0; i < count; i++)
  {
    webots::Node *node = children->getMFNode(i);
    auto *name = node->getField("name");
    if (name)
    {
      (*entities)[name->getSFString()] = node;
    }
  }

  return entities;
}

int main(int argc, char **argv)
{
  std::cout << "Referee addr: " << argv[1] << std::endl;
  std::cout << "Referee port: " << argv[2] << std::endl;

  std::cout << "Yellow addr: " << argv[3] << std::endl;
  std::cout << "Yellow port: " << argv[4] << std::endl;

  std::cout << "Blue addr: " << argv[5] << std::endl;
  std::cout << "Blue port: " << argv[6] << std::endl;

  std::cout << "Vision addr: " << argv[7] << std::endl;
  std::cout << "Vision port: " << argv[8] << std::endl;

  auto referee = std::make_unique<webots::Supervisor>();

  auto time_step = (uint16_t) referee->getBasicTimeStep();

  webots::Field *children = referee->getRoot()->getField("children");

  auto robots = get_robots_references(children);

  auto yellow_robot_ptr = robots->at("YellowRobot0");
  auto yellow_robot = vss::Robot(yellow_robot_ptr);

  std::cout << std::fixed << std::setprecision(2);

  while (referee->step(time_step) != -1)
  {
    auto position = yellow_robot.get_position();

    // std::cout << position[0] << ", " << position[1] << ", " << position[2] << "\n";
  };

  return 0;
}
