#include "ros/ros.h"
#include "epos2/Velocity.h"
#include "wrap.h"
#include "geometry_msgs/Vector3.h"

int main(int argc, char **argv)
{
	// initialising ros stuffs
	ros::init(argc, argv, "pub");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<geometry_msgs::Vector3>("/epos2/cmd_vel",1000);
	
	long int Vx,Vy;
	geometry_msgs::Vector3 tmp;	
	ROS_INFO("Enter Vx"); cin >> Vx; tmp.x=Vx;
	ROS_INFO("Enter Vy"); cin >> Vy; tmp.y=Vy;
	pub.publish(tmp);
	ros::spin();
}

