#include "Serpent.hpp"



Gazebo_movement::Gazebo_movement(ros::NodeHandle *nh)
{
	set_gazebo_pos_pub = nh->advertise<std_msgs::Float64>("/serpent_gazebo/serpent_joint_1_position_controller/command", 1000);
}

void Gazebo_movement::set_gazebo_position(int angle)
{
	std_msgs::Float64 msg;
	msg.data = ANGLE_TO_RADIANT(angle);
	set_gazebo_pos_pub.publish(msg);
}

int Gazebo_movement::get_gazebo_position()
{
	//TODO: still needs to be implemented
	return 1;
}
