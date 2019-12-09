#include <Wire.h>
#include <Adafruit_ADS1015.h>

#include <ros.h>
#include <geometry_msgs/WrenchStamped.h>
#include <ros/time.h>
#include <Ticker.h>

Adafruit_ADS1015 ads1015;

//Set up the ros node and publisher
geometry_msgs::WrenchStamped lc_msg;
ros::Publisher pub_temp("force", &lc_msg);
ros::NodeHandle nh;
Ticker flipper;

void setup()
{
  nh.initNode();
  nh.advertise(pub_temp);
  ads1015.begin();
  flipper.attach_ms(19 ,send_force);
}

long publisher_timer;
// plot out for 10,5,1s.
//test the limit by reducing ticker time till instruction gets skipped or queued.
void send_force()
{
      lc_msg.header.stamp = nh.now();
      lc_msg.wrench.force.x = ads1015.readADC_Differential_0_1();
      pub_temp.publish(&lc_msg);
      nh.spinOnce();
}
void loop() {
}
