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

  uint32_t frame = 0;

  webots::Emitter *yellow_team_emitter = referee->getEmitter("yellow_team");
  webots::Emitter *blue_team_emitter = referee->getEmitter("blue_team");

  yellow_team_emitter->setChannel(0);
  blue_team_emitter->setChannel(1);

  while (referee->step(time_step) != -1)
  {
    frame++;

    yellow_team_emitter->send(&frame, sizeof(frame));

    // yellow_robot_ptr

    // std::cout << position[0] << ", " << position[1] << ", " << position[2] << "\n";
  };

  return 0;
}
