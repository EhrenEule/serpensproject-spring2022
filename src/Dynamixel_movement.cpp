#include "Serpent.hpp"



Dynamixel_movement::Dynamixel_movement(ros::NodeHandle *nh, int call_id)
{
	id = call_id;
	
	portHandler = PortHandler::getPortHandler(DEVICE_NAME);
	packetHandler = PacketHandler::getPacketHandler(PROTOCOL_VERSION);

	if (!portHandler->openPort()) {	throw std::runtime_error( "Failed to open port" );	}

	if (!portHandler->setBaudRate(BAUDRATE)) {	throw std::runtime_error( "Failed to set Baudrate");	}
  
	set_pub = nh->advertise<serpent::Position>("/set_position_topic", 1000);

	get_pub = nh->advertise<serpent::Position>("/get_position_topic", 1000);
}

/*
 * This function takes an angle as an int and sets the motor to that angle,
 * afterwards it also publishes the previously sent angle on the rostopic /set_position_topic
 */ 
void Dynamixel_movement::set_dynamixel_position(int angle)
{
	dxl_comm_result = packetHandler->write4ByteTxRx(
    portHandler, id, ADDR_GOAL_POSITION, ANGLE_TO_POS(angle), &dxl_error);
    
    serpent::Position set_msg;
	set_msg.id = id;
	set_msg.position = ANGLE_TO_POS(angle);
	set_msg.angle = angle;
	set_pub.publish(set_msg);   
}

int Dynamixel_movement::get_dynamixel_position()
{
	int received_position = 0;
	
	dxl_comm_result = packetHandler->read4ByteTxRx(
    portHandler, id, ADDR_PRESENT_POSITION, (uint32_t *)&received_position, &dxl_error);
    
   	serpent::Position get_msg;
	get_msg.id = id;
	get_msg.position = received_position;
	get_msg.angle = POS_TO_ANGLE(received_position);
	get_pub.publish(get_msg);
	return POS_TO_ANGLE(received_position);
}

void Dynamixel_movement::set_dynamixel_PID(int p, int i, int d)
{
	//Sets P_value
	dxl_comm_result = packetHandler->write2ByteTxRx(
    portHandler, id, ADDR_P_GAIN_POSITION, p, &dxl_error);
    
    //Sets I_value
    dxl_comm_result = packetHandler->write2ByteTxRx(
    portHandler, id, ADDR_I_GAIN_POSITION, i, &dxl_error);
    
    //Sets D_value
    dxl_comm_result = packetHandler->write2ByteTxRx(
    portHandler, id, ADDR_D_GAIN_POSITION, d, &dxl_error);
}
