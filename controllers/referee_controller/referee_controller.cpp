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
  auto referee = std::make_unique<webots::Supervisor>();

  auto time_step = (uint16_t) referee->getBasicTimeStep();

  webots::Node *root = referee->getRoot();
  webots::Field *children = root->getField("children");

  auto count = children->getCount();
  std::cout << "Node count: " << count << std::endl;

  auto entities = get_robots_references(children);

  auto yellow_robot = entities->at("YellowRobot0");

  std::cout << std::fixed << std::setprecision(2);

  std::cout << "Server: " << argv[1] << std::endl;
  std::cout << "Port: " << argv[2] << std::endl;

  while (referee->step(time_step) != -1)
  {
    const double (&position)[3] = *reinterpret_cast<const double(*)[3]>(yellow_robot->getPosition());

    // std::cout << position[0] << ", " << position[1] << ", " << position[2] << "\n";
  };

  return 0;
}
