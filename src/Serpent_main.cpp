/*	TODO 
 *  
 * 	-create new classes to create publisher objects, one for the physical robot and one for the gazebo model 
 * 		with set_position and get_poisition functions
 * 
 * 	-implement the serpent digital twin model so it works with the code 
 * 
 * 	-create 2 launch files, one to only control the motor and one to control the motor and the digital twin at the same time
 * 
 * 	TODO NOW: check gazebo model and try to make it listen to the set_position_topic`
 * 
 * 	-check why project can't be build on other systems 
 *  *  * 
 * 
 * 	 _DIGITAL TWIN CHECK HOW TO DUPLICATE ONE SHELL OF THE SERPENT with a specific distance and connect them manually 
 * 
 * 	also position the model verticaly
 * 
 *  check how i can read the angle from the gazebo model and plot it 
 * 
 * write function that sets the motor to the initial position smoothly
 * 
 */

#include "Serpent.hpp"

#define DIGITAL_TWIN

int main(int argc, char ** argv)
{
	
  ros::init(argc, argv, "read_write_node");
  ros::NodeHandle nh;
  
  Dynamixel_movement dynamixel_obj = Dynamixel_movement(&nh, DXL1_ID);
  
  Gazebo_movement gazebo_obj = Gazebo_movement(&nh);

	//set PID values here
	//intital values (800,0,0)
	dynamixel_obj.set_dynamixel_PID(800,0,0);

	//Rate of the while(ros::ok()) loop in Hertz
	ros::Rate r(100);
	
	//this variable defines how often the while loop is going to be executed	
	int max_loops = 5;
	
	//this is the maximum angle the motor will go to
	int max_angle = 180;
	
	//this is the minimum angle the motor will go to
	int min_angle = 100;
	
	//this is the initial position
	int initial_position =100;

	
	//the following variables are just helping variables and are not supposed to be changed
	int error = 0; 
	int current_loop = -1;
	bool is_incrementing = true;
	int received_angle_position = 0;
	int counter = 0;
	int set_position= initial_position;
	bool is_calibered = false;
	
	bool is_initial_pos_smaller_than_current_pos;
	if(initial_position <= dynamixel_obj.get_dynamixel_position()) { is_initial_pos_smaller_than_current_pos = true; }

  while (ros::ok())
  {
	if(is_calibered == false)
	{
		is_calibered = caliber_dynamixel(dynamixel_obj, initial_position, is_initial_pos_smaller_than_current_pos);
	}
	  
	else if(current_loop == max_loops) 
	{	
		ROS_INFO("Program finished/ Average error: %f",(double) error/counter);
		break; 
	} 
	
	else if(set_position >= max_angle) 
	{ 
		is_incrementing = false; 
		set_position--;
	}
	else if(set_position <= min_angle)
	{
		is_incrementing = true;
		set_position++;
		current_loop++;
	}
	else if(is_incrementing == true)
	{
		gazebo_obj.set_gazebo_position(set_position);
		dynamixel_obj.set_dynamixel_position(set_position);
		error = error + abs(set_position - dynamixel_obj.get_dynamixel_position());
		set_position++;
	}
	else if(is_incrementing == false)
	{
		gazebo_obj.set_gazebo_position(set_position);
		dynamixel_obj.set_dynamixel_position(set_position);
		//here the error gets calculated and the get_dynamixel_position() function gets called
		error = error + abs(set_position - dynamixel_obj.get_dynamixel_position());	
		set_position--;
	} 
	
	counter++;
	ros::spinOnce();
	r.sleep();
	}
  return 0;
}

bool caliber_dynamixel(Dynamixel_movement dynamixel_obj, int initial_position, bool is_initial_pos_smaller_than_current_pos)
{
	//then it should decremenet until this is not the case anymore
	if(is_initial_pos_smaller_than_current_pos == true)
	{
		if(dynamixel_obj.get_dynamixel_position() < initial_position) 
		{
			return true;	
		}
		else 
		{ 
			dynamixel_obj.set_dynamixel_position(dynamixel_obj.get_dynamixel_position() - 2);
			return false;	
		}
	}
	//then it should increment until current_position is smaller or equal to initial position
	else
	{
		if(dynamixel_obj.get_dynamixel_position() >= initial_position) 
		{
			return true;	
		}
		else 
		{ 
			dynamixel_obj.set_dynamixel_position(dynamixel_obj.get_dynamixel_position() + 2);
			return false;	
		}
	}
}


