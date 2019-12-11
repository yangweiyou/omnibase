#!/usr/bin/env python
import rospy
import time
from geometry_msgs.msg import WrenchStamped 
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Vector3

max_vel =100
tmp = Twist()
pub = rospy.Publisher('/epos2/cmd_vel', Twist, queue_size=10)

def cb_once(data):

    global init_fx
    init_fx = data.wrench.force.x
    sub_once.unregister()

global sub_once
sub_once = rospy.Subscriber("/force",WrenchStamped,cb_once)

def callback(data):

    v_x = (data.wrench.force.x-init_fx)*max_vel
    tmp.linear = Vector3(v_x,0,0)
    tmp.angular = Vector3(0,0,0)


if __name__ == '__main__':
    rospy.init_node('ft_control', anonymous=True)
    rospy.Subscriber("/force", WrenchStamped, callback)
    
    rate = rospy.Rate(70) #10hz
    while not rospy.is_shutdown():	
    	pub.publish(tmp)	
	rate.sleep()

    print "Start FT Control" 
    print "Initial fx =" + str(init_fx)
    rospy.spin()

















