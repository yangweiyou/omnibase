#include "ros/ros.h"
#include "omnibase/Velocity.h"
#include "wrap.h"
#include "geometry_msgs/Twist.h"

void callback(const geometry_msgs::Twist &vel)
{
	unsigned int ulErrorCode = 0;
	long int Vx,Vy,w,v1,v2,v3;
	int z=23.4;// in cm
	Vx=vel.linear.x;
	Vy=vel.linear.y;
	w=vel.angular.z;
	v1 = Vy + w*z;	
	v2 = ((-sqrt(3)/2)*Vx) + (-0.5*Vy) + w*z;
	v3 = (sqrt(3)/2)*Vx + (-0.5*Vy) + w*z;

	// Moving with calculated velocities
	MoveWithVelocity(g_pKeyHandle, 1, (long)v1, &ulErrorCode);
	MoveWithVelocity(g_pKeyHandle, 2, (long)v2, &ulErrorCode);
	//MoveWithVelocity(g_pKeyHandle, 3, (long)v3, &ulErrorCode);
	

}


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
	
	//Activate all drivers
	SetEnableState(g_pKeyHandle, 1, &ulErrorCode);
	ActivateProfileVelocityMode(g_pKeyHandle, 1, &ulErrorCode);
	SetEnableState(g_pKeyHandle, 2, &ulErrorCode);
	ActivateProfileVelocityMode(g_pKeyHandle, 2, &ulErrorCode);
	//SetEnableState(g_pKeyHandle, 3, &ulErrorCode);
	//ActivateProfileVelocityMode(g_pKeyHandle, 3, &ulErrorCode);
	
	
	// initialising ros stuffs
	ros::init(argc, argv, "control");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("omnibase/cmd_vel" , 1000 ,&callback);
	ros::spin();
}
 
