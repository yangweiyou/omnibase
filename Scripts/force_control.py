#!/usr/bin/env python
import rospy
import time
from geometry_msgs.msg import WrenchStamped 
from geometry_msgs.msg import Twist
from geometry_msgs.msg import Vector3

max_vel =100

pub = rospy.Publisher('/epos2/cmd_vel', Twist, queue_size=10)


def cb_once(data):

    global init_fx
    init_fx = data.wrench.force.x
    sub_once.unregister()

global sub_once
sub_once = rospy.Subscriber("/force",WrenchStamped,cb_once)

def callback(data):

    v_x = (data.wrench.force.x-init_fx)*max_vel
    #now = rospy-get_rostime()

    tmp = Twist()
    tmp.linear = Vector3(v_x,0,0)
    tmp.angular = Vector3(0,0,0)
    pub.publish(tmp)

if __name__ == '__main__':
    rospy.init_node('ft_control', anonymous=True)
    rospy.Subscriber("/force", WrenchStamped, callback)

    print "Start FT Control" 
    print "Initial fx =" + str(init_fx)
    rospy.spin()
