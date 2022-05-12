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
 * 
 * 	-check why project can't be build on other systems 
 * 
 *  -
 * 
 *  -maybe have a look how to create a user interface
 * 
 *  -check how to kill program by command so it goes to 0 
 */

#include "Serpent.hpp"

//#define DIGITAL_TWIN

int main(int argc, char ** argv)
{
	
  ros::init(argc, argv, "read_write_node");
  ros::NodeHandle nh;
  
  //std::boolean digital_twin =  nh.hasParam("digital_twin");
  //nh.hasParam("digital_twin", digital_twin);
  
	/*if(nh.hasParam("twin") 
	{	
		ROS_INFO("digtial twin activaed");	
	}*/
  //if( !digital_twin ) {	ROS_INFO("digtial twin not activaed");	}

  Dynamixel_movement dynamixel_obj = Dynamixel_movement(&nh, DXL1_ID);
  
  //if def digital twin
	//Gazebo_movement gazebo_obj = Gazebo_movement(&nh, DXL1)
  
  /*
 * Creates the ros topics for the digital twin if it is defined 
 */ 
#ifdef DIGITAL_TWIN		
	#ifdef DXL1_ID
		ros::Publisher set_gazebo_pos_1_pub = nh.advertise<std_msgs::Float64>("/rrbot/joint1_position_controller/command", 1000);
	#endif  
#endif


	//set PID values here
	//intital values (800,0,0)
	dynamixel_obj.set_dynamixel_PID(800,0,0);

	//Rate in Hertz
	ros::Rate r(100);
	
	//this variable defines how often the while loop is going to be executed	
	int loop_repetitions = 500;
	
	//this is the maximum angle the motor will go to
	//you can change this variable to whichever angle you want
	int max_angle = 50;
	
	//this is the minimum angle the motor will go to
	//you can change this variable to whichever angle you want
	int min_angle = 0;
	
	//the following variables are just helping variables and are not supposed to be changed
	int error = 0; 
	bool is_incrementing = true;
	int received_angle_position = 0;
	int counter = 0;
	int set_position =0;

  while (ros::ok())
  {
	if(counter>= loop_repetitions && counter%max_angle == 0) 
	{	
		ROS_INFO("Program finished/ Average error: %f",(double) error/counter);
		break; 
	} 
	
	if(set_position >= max_angle) 
	{ 
		is_incrementing = false; 
		set_position--;
	}
	else if(set_position <= min_angle)
	{
		is_incrementing = true;
		set_position++;
	}
	else if(is_incrementing == true)
	{
		set_position++;
		dynamixel_obj.set_dynamixel_position(set_position);
		error = error + abs(set_position - dynamixel_obj.get_dynamixel_position());
	}
	else if(is_incrementing == false)
	{
		set_position--;
		dynamixel_obj.set_dynamixel_position(set_position);
		
		//here the error gets calculated and the get_dynamixel_position() function gets called
		error = error + abs(set_position - dynamixel_obj.get_dynamixel_position());	
	}
	
	counter++;
	ros::spinOnce();
	r.sleep();
	}
  return 0;
}




/*
 * Sets the position of the Dynamixel
 * 
 * id: the id of the dynamixel
 * angle: the desired angle of the motor
 * set_position_pub: The publisher object that publishes the angle and id onto a topic
 */ 
/*void setPosition(int id, int angle, ros::Publisher set_position_pub, ros::Publisher set_gazebo_pos_1_pub)
{
	dxl_error = 0;
	dxl_comm_result = COMM_TX_FAIL;
  
	serpent::Position set_msg;
	set_msg.id = id;
	set_msg.position = ANGLE_TO_POS(angle);
	set_msg.angle = angle;
	set_position_pub.publish(set_msg);
	   
	dxl_comm_result = packetHandler->write4ByteTxRx(
    portHandler, set_msg.id, ADDR_GOAL_POSITION, set_msg.position, &dxl_error);
    
    #ifdef DXL1_ID 
			if(id == DXL1_ID)
			{
				std_msgs::Float64 msg;
				msg.data = DE_2_R(angle);
				set_gazebo_pos_1_pub.publish(msg);
			}
    #endif
}

/*
 * Gets the position of the Dynamixel
 * 
 * id: the id of the dynamixel
 * get_position_pub: The publisher object that publishes the received position onto a topic 
 
void getPosition(int id, ros::Publisher get_position_pub)
{
	int received_position = 0;
	
	dxl_comm_result = packetHandler->read4ByteTxRx(
    portHandler, id, ADDR_PRESENT_POSITION, (uint32_t *)&received_position, &dxl_error);
    
    
   	serpent::Position get_msg;
	get_msg.id = id;
	get_msg.position = received_position;
	get_msg.angle = POS_2_ANGLE(received_position);
	get_position_pub.publish(get_msg);
	
	#ifdef DIGITAL_TWIN
		
    #endif
}
*/


