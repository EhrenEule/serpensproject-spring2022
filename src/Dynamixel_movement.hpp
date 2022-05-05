#include "dynamixel_sdk/dynamixel_sdk.h"
#include <ros/ros.h>
#include "serpent/Position.h"
#include <stdexcept>


using namespace dynamixel;


// Control table address
#define ADDR_TORQUE_ENABLE    64
#define ADDR_GOAL_POSITION    116
#define ADDR_PRESENT_POSITION 132

// Protocol version
#define PROTOCOL_VERSION      2.0             // Default Protocol version of DYNAMIXEL X series.

// Default setting
#define DXL1_ID               1               // DXL1 ID
#define BAUDRATE              57600           // Default Baudrate of DYNAMIXEL X series
#define DEVICE_NAME           "/dev/ttyACM0"  // [Linux] To find assigned port, use "$ ls /dev/ttyUSB*" command

#define ANGLE_TO_POS(x) (x*11.375)
#define POS_2_ANGLE(x) (x/11.375)



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
		void get_dynamixel_position();
};
