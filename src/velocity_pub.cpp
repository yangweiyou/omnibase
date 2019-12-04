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
	
	ROS_INFO ("Choose Node");
	cin >> node;
	ROS_INFO ("node id = %d", node);
	SetEnableState(g_pKeyHandle, node, &ulErrorCode);
	ActivateProfileVelocityMode(g_pKeyHandle, node, &ulErrorCode);
	
	// initialising ros stuffs
	ros::init(argc, argv, "epos2");
	ros::NodeHandle n;
	ros::Publisher vel_pub = n.advertise<std_msgs::Int32>("vel",1000);
	ROS_INFO("Ready to move.");	
	
	long int targetVelocity;
	ROS_INFO("Enter target velocity");
	cin >> targetVelocity;
	ROS_INFO("request: targetVelocity=%ld", targetVelocity);
	//MoveWithVelocity(g_pKeyHandle, g_usNodeId, 1000, &ulErrorCode);
	MoveWithVelocity(g_pKeyHandle, node, (long)targetVelocity, &ulErrorCode);
	ros::spin();
}
