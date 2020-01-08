#include "ros/ros.h"
#include "omnibase/Velocity.h"
#include "wrap.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{
	// initialising ros stuffs
	ros::init(argc, argv, "pub_vel");
	ros::NodeHandle n;
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/omnibase/cmd_vel",1000);
	
	long int Vx,Vy,w;
	geometry_msgs::Twist tmp;	
	ROS_INFO("Enter Vx"); cin >> Vx; tmp.linear.x = Vx;
	ROS_INFO("Enter Vy"); cin >> Vy; tmp.linear.y = Vy;
	ROS_INFO("Enter w"); cin >> w; tmp.angular.z = w;
	pub.publish(tmp);
	ros::spin();
}
