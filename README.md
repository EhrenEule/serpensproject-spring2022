# serpensproject-spring2022

Repository for the EPS-Serpens project in the spring semester 2022. 
This repository only includes the catkin package with the ROS code.
You can find the catkin package including the gazebo code for the virtual twin [here](https://github.com/EhrenEule/serpensproject-spring2022-gazebo).

### Dependencies:

You need to clone the following two github projects in your catkin_ws/src folder 

[rosserial](https://github.com/ros-drivers/rosserial) 

[DynamixelSDK](https://github.com/ROBOTIS-GIT/DynamixelSDK)


### Tips for the next group:

You’ll be working with a 3D modelling programme named ‘Gazebo’, which is not available on Windows, so we advise you all to install a Virtual Machine that runs on Linux-Ubuntu, so you can install it there it might take up a lot of space, so you should allocate a lot of memory to it, like 40 GB). You can look for the commands for the terminal on the Gazebo website.

ROS is the most important piece, as it will be where you write the commands for the modules, initialize the Gazebo simulation worlds, and receive data from the programmes that are currently running. You should also install 'rqt' console, an interface to see the difference between the desired and the actual position of the joints.


--> Don't forget that each time you change a script for the Serpens you must run the command catkin_make

If you want to check if the Dynamixel is being recognised by the machine, run the find_dynamixel code. If it doesn't find it, install a programme called 'Dynamixel Wizard2.0' and run a firmware recovery. After you get the results and can see the servo, hit the 'enable torque' option and voila.

### Commands to start the software:

> rosrun serpent Serpent_main

### Code overview

The main file is src/Serpent_main, where objects of the classes Dynamixel_movement and Gazebo_movement are created.
Serpent.hpp is the header file for all source code files.
