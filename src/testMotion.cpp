#include "ros/ros.h"
#include "epos2/Velocity.h"
#include "wrap.h"
#include "geometry_msgs/Vector3.h"

void callback(const geometry_msgs::Vector3 &vel)
{
	unsigned int ulErrorCode = 0;
	long int Vx,Vy,w,v1,v2,v3;
	int z=23.4;// in cm
	//ROS_INFO("Enter Vx"); cin >> Vx;
	//ROS_INFO("Enter Vy"); cin >> Vy;
	Vx=vel.x;
	Vy=vel.y;
	w=vel.z;
	// from https://www.maxongroup.fr/medias/sys_master/root/8806895255582/13-216-en.pdf
		

	v1 = Vy + w*z;
	v2 = ((-sqrt(3)/2)*Vx) + (-0.5*Vy) + w*z;
	v3 = (sqrt(3)/2)*Vx + (-0.5*Vy) + w*z;

	
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
	
	//Activate both driver
	SetEnableState(g_pKeyHandle, 1, &ulErrorCode);
	ActivateProfileVelocityMode(g_pKeyHandle, 1, &ulErrorCode);
	SetEnableState(g_pKeyHandle, 2, &ulErrorCode);
	ActivateProfileVelocityMode(g_pKeyHandle, 2, &ulErrorCode);
	
	// initialising ros stuffs
	ros::init(argc, argv, "listen");
	ros::NodeHandle n;
	ros::Subscriber sub = n.subscribe("epos2/cmd_vel" , 1000 ,&callback);
	ros::spin();
}
 
