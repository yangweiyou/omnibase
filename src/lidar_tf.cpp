#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "lidar_tf");
  ros::NodeHandle n;


  static tf::TransformBroadcaster br1;
  static tf::TransformBroadcaster br2;
  tf::Transform laser1;
  tf::Transform laser2;
  ros::Rate rate(50.0);

  while(n.ok()){
    laser1.setOrigin( tf::Vector3(0.1, 0.07, 0.8) ); // coordinates of lidar1
    //laser1.setRotation( tf::Quaternion(0.5, 0.5, 0.5 ,0.5) );
    laser1.setRotation( tf::Quaternion(0, 0, 0.707 ,0.707) );
    br1.sendTransform(tf::StampedTransform(laser1, ros::Time::now(), "base_link","laser1"));

    laser2.setOrigin( tf::Vector3(-0.1, -0.07, 0.8) ); // coordinates of lidar2
    //laser2.setRotation( tf::Quaternion(0, 0, 1, 0) );
    laser2.setRotation( tf::Quaternion(0, 0, -0.707, 0.707) );
    br2.sendTransform(tf::StampedTransform(laser2, ros::Time::now(),"base_link", "laser2"));
    rate.sleep();
  }
}

