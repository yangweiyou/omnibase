#include "ros/ros.h"
#include "epos2/Position.h"
#include "wrap.h"
#include "std_msgs/Int32.h"
int main(int argc, char **argv)
{

int lResult = MMC_FAILED;
	unsigned int ulErrorCode = 0;
	// Set parameter for usb IO operation
	SetDefaultParameters();
	// open device
	if((lResult = OpenDevice(&ulErrorCode))!=MMC_SUCCESS)
	{
		LogError("OpenDevice", lResult, ulErrorCode);
		return lResult;
	}
	
	SetEnableState(g_pKeyHandle, g_usNodeId, &ulErrorCode);
	ActivateProfileVelocityMode(g_pKeyHandle, g_usNodeId, &ulErrorCode);
	
	// initialising ros stuffs
	ros::init(argc, argv, "epos2");
	ros::NodeHandle n;
	ros::Publisher pos_pub = n.advertise<std_msgs::Int32>("pos",1000);
	ROS_INFO("Ready to move.");	
	
	long int targetPosition;
	int isAbsolute =0;
	ROS_INFO("Enter target position");
	cin >> targetPosition;

	ROS_INFO("request: target position=%ld", (long int)targetPosition);
	//MoveToPosition(g_pKeyHandle, g_usNodeId, (long)targetPosition, isAbsolute, &ulErrorCode);
	MoveToPosition(g_pKeyHandle, g_usNodeId, 1000, 0, &ulErrorCode);
	sleep(100);

	short current;
	int position_new;
	ROS_INFO("now read position");
	get_position(g_pKeyHandle, g_usNodeId, &position_new, &ulErrorCode);
	ROS_INFO("Current Position = %d", position_new);
	
	//disable epos
	SetDisableState(g_pKeyHandle, g_usNodeId, &ulErrorCode);
	//close device
	if((lResult = CloseDevice(&ulErrorCode))!=MMC_SUCCESS)
	{
		LogError("CloseDevice", lResult, ulErrorCode);
		return lResult;
	}
	return 0;
}
