/*
 * Header file for the serpent project

*/

#ifndef SERPENT_HPP
#define SERPENT_HPP


#include "dynamixel_sdk/dynamixel_sdk.h"
#include <ros/ros.h>
#include "serpent/Position.h"
#include <stdexcept>
#include <cstdlib>
#include "std_msgs/Float64.h"


using namespace std;



using namespace dynamixel;


// Control table address
#define ADDR_TORQUE_ENABLE	  64
#define ADDR_GOAL_POSITION    116
#define ADDR_PRESENT_POSITION 132

#define ADDR_P_GAIN_POSITION  84	
#define ADDR_I_GAIN_POSITION  82	
#define ADDR_D_GAIN_POSITION  80


// Protocol version
#define PROTOCOL_VERSION      2.0             // Default Protocol version of DYNAMIXEL X series.

// Default setting
#define DXL1_ID               1               // DXL1 ID
#define BAUDRATE              57600           // Default Baudrate of DYNAMIXEL X series
#define DEVICE_NAME           "/dev/ttyACM0"  // [Linux] To find assigned port, use "$ ls /dev/ttyUSB*" command

#define ANGLE_TO_POS(x) (x*11.375)
#define POS_TO_ANGLE(x) (x/11.375)
#define ANGLE_TO_RADIANT(x) ((x*2*M_PI)/360)


class Dynamixel_movement
{
	public:
		int id;
		ros::Publisher set_pub;
		ros::Publisher get_pub;
		uint8_t dxl_error = 0;
		int dxl_comm_result = COMM_TX_FAIL; 
		PortHandler * portHandler;
		PacketHandler * packetHandler;
				
		Dynamixel_movement(ros::NodeHandle *nh, int id);	
		void set_dynamixel_position(int);
		int get_dynamixel_position();
		void set_dynamixel_PID(int p, int i, int d);

};

class Gazebo_movement
{
	public:
		ros::Publisher set_gazebo_pos_pub;
		
		Gazebo_movement(ros::NodeHandle *nh);
		void set_gazebo_position(int);
		int get_gazebo_position();
};

bool caliber_dynamixel(Dynamixel_movement dynamixel_obj, int initial_position, bool is_initial_pos_smaller_than_current_pos); //function prototype


#endif

