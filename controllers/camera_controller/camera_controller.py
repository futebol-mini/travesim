"""camera_controller controller."""

# You may need to import some classes of the controller module. Ex:
#  from controller import Robot, Motor, DistanceSensor
import os
import sys
from datetime import datetime
from math import atan2
from typing import cast

import cv2
import matplotlib.pyplot as plt
import numpy as np
from controller import Camera, Supervisor

ROBOTS = [
    "YellowRobot0",
    "YellowRobot1",
    "YellowRobot2",
    "BlueRobot0",
    "BlueRobot1",
    "BlueRobot2",
    "VssBall",
]

supervisor = Supervisor()

children = supervisor.getRoot().getField("children")

robot_dict = {}

for i in range(children.count):
    try:
        scene_node = children.getMFNode(i)  # type: ignore
        robot_dict[scene_node.getField("name").getSFString()] = scene_node
    except:  # noqa: E722
        pass

timestep = int(supervisor.getBasicTimeStep())

camera = cast(Camera, supervisor.getDevice("camera"))
camera.enable(timestep)

uuid = datetime.now().strftime("%Y-%m-%d-%H:%M:%S")

os.makedirs(f"output/{uuid}")

# Get camera dimensions
width = camera.getWidth()
height = camera.getHeight()

print("Camera started")

frame = 0
with open(f"output/{uuid}/data.csv", "w") as output_file:
    output_file.write("image")
    for robot in ROBOTS:
        if robot == "VssBall":
            output_file.write(f",{robot}_x,{robot}_y")
        else:
            output_file.write(f",{robot}_x,{robot}_y,{robot}_yaw")
    output_file.write("\n")

    while supervisor.step(timestep) != -1 and frame < 1000:  # type: ignore
        frame += 1
        image_name = f"output/{uuid}/{uuid}_{frame:04d}.png"
        camera.saveImage(image_name, 100)

        output_file.write(image_name)
        for robot in ROBOTS:
            pos = robot_dict[robot].getPosition()
            rot = robot_dict[robot].getOrientation()
            if robot == "VssBall":
                output_file.write(f",{pos[0]:.5f},{pos[1]:.5f}")
            else:
                yaw = atan2(rot[3], rot[0])
                output_file.write(f",{pos[0]:.5f},{pos[1]:.5f},{yaw:.5f}")

        output_file.write("\n")
        print(f"Frame: {frame}")

supervisor.simulationSetMode(Supervisor.SIMULATION_MODE_PAUSE)  # type: ignore
print("Controller terminated")
