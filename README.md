serpensproject-spring2022

Repository for the EPS-Serpens project in the spring semester 2022

IMPORTANT!!
<<<<<<< HEAD Projects you need to clone into your catkin_ws/src Folder

TIPS FOR THE NEXT GROUP!!! You’ll be working with a 3D modelling programme named ‘Gazebo’, which is not available on Windows, so we advise you all to install a Virtual Machine that runs on Linux-Ubuntu, so you can install it there (Furthermore, it might take up a lot of space, so you should put a lot of memory in it, like 40 GB). You can look for the commands for the terminal on the Gazebo website

ROS is the most important piece, as it will be where you write the commands for the modules, initialize the Gazebo simulation worlds, and receive data from the programmes that are currently running. You should also install 'rqt' console, an interface to see the difference between the desired and the actual position of the joints.

We used an OpenCM 9.04 with the OpenCM 450 XP expansion pack circuit board(CB) for the control part, and the XM430-W210-T servo motor
To avoid some extra work, you can open the .bashrc file (you can see it from the files if you type ctrl+h to show hidden filles, and write on the very end: source /opt/ros/noetic/setup.bash cd catkin_ws source devel/setup.bash cd .. This will setup ROS for you each time you open a new terminal, so you avoid writing the same thing over and over
--> Don't forget that each time you change a script for the Serpens you must run the command catkin_make

You need to clone the following two github projects in your catkin_ws/src folder 

rosserial (https://github.com/ros-drivers/rosserial) 
DynamixelSDK (https://github.com/ROBOTIS-GIT/DynamixelSDK)

COMMANDS TO CONTROL THE GAZEBO DIGITAL TWIN:

(On the terminal)

    To create a Roscore (always in the beggining) --> roscore
    To open the rrbot's Gazebo world --> roslaunch rrbot_gazebo rrbot_world.launch
    To be able to control the joints position --> roslaunch rrbot_control rrbot_control.launch
    To open an interface to watch the joints plots (and control it from a different environment) --> rosrun rqt_gui rqt_gui
    To control the joint position directly from the terminal(example) --> rostopic pub -1 /rrbot/joint1_position_controller/command std_msgs/Float64 "data: 1.5"
    A simple script to see if the Virtual Box recognizes the board and the dynamixel --> rosrun dynamixel_workbench_controller find_dynamixel /dev/(port of the usb cable)

<<<<<<< HEAD

                            089278a83b923e0925a8ff54715a0023829a3f2e

How to get a Joint to move in Gazebo through the microcontroller and ros

    Download the OpenCM library for the Arduino IDE (https://emanual.robotis.com/docs/en/parts/controller/opencm904/#development-environment ,the tutorial is under 8.3 on the website)

    Upload "Hello WorldGazebo" File through ArduinoIDE onto the micocontroller

    Start roscore, the gazebo world and the controllers (the same stuff you started to get the joint to move through the terminal)

    Run this command 'rosrun rosserial_python serial_node.py /dev/ttyACM0' and substitute the last part with your own port where the microcontroller is connected to

To test if data gets published to the desired topic you can use the command 'rostopic echo /rrbot/joint1_position_controller/command' and see if there is any data getting published

Install Dynamixel Wizard 2. It's a tool to manage Dynamixel. You can use to scan for the board and motor. If you don't see them, you can run a Firmware Recovery process, ONE AT A TIME. Once it appears, enable the torque and try controlling it with the wheel visible there
After you successfully got the motors recognize, you should be able to run the programme 'read_write_node', which let's you control the position of the motor, and the program we've created, that let's define a continuous 180º movement. Please always be carefull when managing the motors while the module is all assembled, an incorrect movement by the motor could cause the outer shell to shatter.
