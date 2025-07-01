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
#include <iomanip> // for std::fixed and std::setprecision

// This is the main program of your controller.
// It creates an instance of your Robot instance, launches its
// function(s) and destroys it at the end of the execution.
// Note that only one instance of Robot should be created in
// a controller program.
// The arguments of the main function can be specified by the
// "controllerArgs" field of the Robot node
int main(int argc, char **argv)
{

  std::cout << "Les gooo" << "\n";
  // create the Robot instance.
  std::cout << "Get supervisor" << "\n";

  auto referee = std::make_unique<webots::Supervisor>();

  // get the time step of the current world.
  auto time_step = (int)referee->getBasicTimeStep();

  std::cout << "Get robot" << "\n";

  // webots::Node *yellow_robot = referee->getFromDef("YellowRobot0");

  webots::Node *root = referee->getRoot();
  std::cout << "Passou da chamada\n" << "Node type: " << root->getType() << "\n";
  // if (!yellow_robot)
  // {
  //   std::cout << "Quebrou!\n";
  //   // std::exit(-1);
  // }

  std::cout << "Get children\n";
  webots::Field* children = root->getField("children");

  if (!children)
  {
    std::cout << "Quebrou 2!\n";
    std::exit(-1);
  }

  auto count = children->getCount();
  std::cout << "Node count: " << count << std::endl;

  for (int i = 0; i < count; i++)
  {
    // std::cout << "node\n";
    webots::Node * node =  children->getMFNode(i);
    auto *name = node->getField("name");
    if(name)
      std::cout << "-> " << name->getSFString() << std::endl;
    else
      std::cout << "-> " << "NoName" << std::endl;
  }
                                                      
  webots::Node *yellow_robot = referee->getFromDef("YellowRobot0");
  if (!yellow_robot)
  {
    std::cout << "Quebrou 3!\n";
    std::exit(-1);
  }
  

  // You should insert a getDevice-like function in order to get the
  // instance of a device of the robot. Something like:
  //  Motor *motor = robot->getMotor("motorname");
  //  DistanceSensor *ds = robot->getDistanceSensor("dsname");
  //  ds->enable(timeStep);

  // Main loop:
  // - perform simulation steps until Webots is stopping the controller
  // std::cout << std::fixed << std::setprecision(2);

  // const double (*position)[3] = reinterpret_cast<const double (*)[3]>(yellow_robot->getPosition());
  // std::cout << position[0] << ", " << position[1] << ", " << position[2] << "\n";

  while (referee->step(time_step) != -1)
  {

    // const double (&position)[3] = *const_cast<const double(*)[3]>(root->getPosition());

    // std::span<const double, 3> position(root->getPosition(), 3);
    // std::cout << "Position: ";


    // const double (*position)[3] = reinterpret_cast<const double (*)[3]>(yellow_robot->getPosition());

    // std::cout << position[0] << ", " << position[1] << ", " << position[2] << "\n";
  };

  // Enter here exit cleanup code.

  // delete referee;
  return 0;
}
