# serpensproject-spring2022

Repository for the EPS-Serpens project in the spring semester 2022. 
This repository only includes the catkin package with the ROS code.
You can find the catkin package including the gazebo code for the virtual twin [here](https://github.com/EhrenEule/serpensproject-spring2022-gazebo
).

### Dependencies:

You need to clone the following two github projects in your catkin_ws/src folder 

[rosserial](https://github.com/ros-drivers/rosserial) 

[DynamixelSDK](https://github.com/ROBOTIS-GIT/DynamixelSDK)


### Tips for the next group:

You’ll be working with a 3D modelling programme named ‘Gazebo’, which is not available on Windows, so we advise you all to install a Virtual Machine that runs on Linux-Ubuntu, so you can install it there (Furthermore, it might take up a lot of space, so you should put a lot of memory in it, like 40 GB). You can look for the commands for the terminal on the Gazebo website

ROS is the most important piece, as it will be where you write the commands for the modules, initialize the Gazebo simulation worlds, and receive data from the programmes that are currently running. You should also install 'rqt' console, an interface to see the difference between the desired and the actual position of the joints.

We used an OpenCM 9.04 with the OpenCM 450 XP expansion pack circuit board(CB) for the control part, and the XM430-W210-T servo motor

--> Don't forget that each time you change a script for the Serpens you must run the command catkin_make

For some reason the motor is not always able to enable torque. To fix this we installed a program called 'Dynamixel Wizard 2' and manually enabled torque there. 

### Commands to start the software:

> rosrun serpent Serpent_main

### Code overview

The main file is src/Serpent_main, where objects of the classes Dynamixel_movement and Gazebo_movement are created.
Serpent.hpp is the header file for all source code files.
