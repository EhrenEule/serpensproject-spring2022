#include "Dynamixel_movement.hpp"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"


void setPosition(int id, int angle, ros::Publisher set_pos_pub, ros::Publisher set_gazebo_pos_1_pub); 	//function prototype
void getPosition(int id, ros::Publisher get_position_pub); 	//function prototype
