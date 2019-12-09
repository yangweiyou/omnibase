#include "ros/ros.h"
#include "epos2/Velocity.h"
#include "wrap.h"
#include "std_msgs/Int32.h"
int main(int argc, char **argv)
{

int lResult = MMC_FAILED;
	unsigned int ulErrorCode = 0;
	int node; 
	// Set parameter for usb IO operation
	SetDefaultParameters();
	// open device
	if((lResult = OpenDevice(&ulErrorCode))!=MMC_SUCCESS)
	{
		LogError("OpenDevice", lResult, ulErrorCode);
		return lResult;
	}
	
	SetEnableState(g_pKeyHandle, 1, &ulErrorCode);
	ActivateProfileVelocityMode(g_pKeyHandle, 1, &ulErrorCode);

	SetEnableState(g_pKeyHandle, 2 , &ulErrorCode);
	ActivateProfileVelocityMode(g_pKeyHandle, 2, &ulErrorCode);
	
	// initialising ros stuffs
	ros::init(argc, argv, "epos2");
	ros::NodeHandle n;
	ros::Publisher vel_pub = n.advertise<std_msgs::Int32>("vel",1000);
	ROS_INFO("Ready to move.");	
	
	long int v1,v2;
	v1=000;v2=000;
	ROS_INFO("V1 : %ld", v1);
	ROS_INFO("V2 : %ld", v2);
	MoveWithVelocity(g_pKeyHandle, 1, (long)v1, &ulErrorCode);
	MoveWithVelocity(g_pKeyHandle, 2, (long)v2, &ulErrorCode);
	
	//disable epos
	SetDisableState(g_pKeyHandle, g_usNodeId, &ulErrorCode);
	//close device
	if((lResult = CloseDevice(&ulErrorCode))!=MMC_SUCCESS)
	{
		LogError("CloseDevice", lResult, ulErrorCode);
		return lResult;
	}
}
