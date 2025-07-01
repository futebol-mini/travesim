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

int main(int argc, char **argv)
{

  std::cout << "Les gooo" << "\n";
  // create the Robot instance.
  std::cout << "Get supervisor" << "\n";

  auto referee = std::make_unique<webots::Supervisor>();

  // get the time step of the current world.
  auto time_step = (int)referee->getBasicTimeStep();

  std::cout << "Get robot" << "\n";

  webots::Node *root = referee->getRoot();

  std::cout << "Get children\n";
  webots::Field *children = root->getField("children");

  if (!children)
  {
    std::cout << "Quebrou 2!\n";
    std::exit(-1);
  }

  auto count = children->getCount();
  std::cout << "Node count: " << count << std::endl;

  std::unordered_map<std::string, webots::Node *> entities = {
      {"YellowRobot0", nullptr},
      {"YellowRobot1", nullptr},
      {"YellowRobot2", nullptr},
      {"BlueRobot0", nullptr},
      {"BlueRobot1", nullptr},
      {"BlueRobot2", nullptr},
  };

  for (int i = 0; i < count; i++)
  {
    webots::Node *node = children->getMFNode(i);
    auto *name = node->getField("name");
    if (name)
    {
      std::cout << "-> " << name->getSFString() << std::endl;
      entities[name->getSFString()] = node;
    }
    else
      std::cout << "-> " << "NoName" << std::endl;
  }

  auto yellow_robot = entities["YellowRobot0"];

  if (!yellow_robot)
  {
    std::cout << "Quebrou 3!\n";
    std::exit(-1);
  }
  std::cout << std::fixed << std::setprecision(2);
  while (referee->step(time_step) != -1)
  {

    // const double (&position)[3] = *const_cast<const double(*)[3]>(root->getPosition());

    // std::span<const double, 3> position(root->getPosition(), 3);
    // std::cout << "Position: ";

    // const double (*position)[3] = reinterpret_cast<const double (*)[3]>(yellow_robot->getPosition());
    const double *position = yellow_robot->getPosition();

    std::cout << position[0] << ", " << position[1] << ", " << position[2] << "\n";
  };

  // Enter here exit cleanup code.

  // delete referee;
  return 0;
}
