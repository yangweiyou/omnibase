#!/usr/bin/env python
import rospy
import time
from geometry_msgs.msg import WrenchStamped 
from geometry_msgs.msg import Vector3Stamped

max_vel = 500
max_yaw = 500

pub = rospy.Publisher('/epos2/cmd_vel', Vector3Stamped, queue_size=10)


def cb_once(data):

    global init_fx
    init_fx = data.wrench.force.x
    sub_once.unregister()

global sub_once
sub_once = rospy.Subscriber("/force",WrenchStamped,cb_once)

def callback(data):

    v_x = data.wrench.force.x-init_fx*max_vel
    now = rospy-get_rostime()

    tmp = Vector3()
    tmp.vector.x=v_x
    tmp.vector.y=tmp.vector.z=0
    tmp.header.stamp = now
    pub.publish(tmp)

if __name__ == '__main__':
    rospy.init_node('ft_control', anonymous=True)
    rospy.Subscriber("/force", WrenchStamped, callback)

    print "Start FT Control" 
    print "Initial fx =" + str(init_fx)
    rospy.spin()
