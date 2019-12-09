/*
  Basic Ticker usage

  Ticker is an object that will call a given function with a certain period.
  Each Ticker calls one function. You can have as many Tickers as you like,
  memory being the only limitation.

  A function may be attached to a ticker and detached from the ticker.
  There are two variants of the attach function: attach and attach_ms.
  The first one takes period in seconds, the second one in milliseconds.

  The built-in LED will be blinking.
*/
#include <ros.h>
#include <geometry_msgs/WrenchStamped.h>
#include <ros/time.h>
#include <Ticker.h>
#include "HX711.h"


#define DOUT 2
#define CLK  16

HX711 scale;

float calibration_factor = -883.0;


//Set up the ros node and publisher
geometry_msgs::WrenchStamped lc_msg;
ros::Publisher pub_temp("force", &lc_msg);
ros::NodeHandle nh;
Ticker flipper;

void setup()
{
  nh.initNode();
  nh.advertise(pub_temp);
  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor);
  scale.tare();
  flipper.attach_ms(92,send_force);
}

long publisher_timer;
// plot out for 10,5,1s.
//test the limit by reducing ticker time till instruction gets skipped or queued.
void send_force()
{
      lc_msg.header.stamp = nh.now();
      lc_msg.wrench.force.x = scale.get_units();
      pub_temp.publish(&lc_msg);
      nh.spinOnce();
}
void loop() {
}
