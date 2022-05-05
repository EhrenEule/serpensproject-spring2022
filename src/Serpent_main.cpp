/*	TODO 
 *  
 * 	-create new classes to create publisher objects, one for the physical robot and one for the gazebo model 
 * 		with set_position and get_poisition functions
 * 	
 * 	-check how to integrate PID
 *  
 * 	-update github so its just the project 
 * 
 * 	-implement the serpent digital twin model so it works with the code 
 * 
 * 	-create 2 launch files, one to only control the motor and one to control the motor and the digital twin at the same time
 * 
 * 	TODO NOW: check gazebo model and try to make it listen to the set_position_topic
 * `
 */

#include "Serpent_main.hpp"

using namespace dynamixel;

#define DE_2_R(x) ((x*2*M_PI)/360)
#define DIGITAL_TWIN

int main(int argc, char ** argv)
{
  ros::init(argc, argv, "read_write_node");
  ros::NodeHandle nh;
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

  //Rate in Hertz
  ros::Rate r(100);
	
	int counter =0;
	bool is_incrementing = true;
  
  while (ros::ok())
  {
	
	if(counter >= 180) 
	{ 
		is_incrementing = false; 
		counter--;
	}
	else if(counter<=0)
	{
		is_incrementing = true;
		counter++;
	}
	else if(is_incrementing == true)
	{
		counter++;
		dynamixel_obj.set_dynamixel_position(counter);
		dynamixel_obj.get_dynamixel_position();
	}
	else if(is_incrementing == false)
	{
		counter--;
		dynamixel_obj.set_dynamixel_position(counter);
		dynamixel_obj.get_dynamixel_position();
	}

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


