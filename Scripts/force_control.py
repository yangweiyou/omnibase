#!/usr/bin/env python
import rospy
import time
from geometry_msgs.msg import WrenchStamped 
from geometry_msgs.msg import Vector3

max_vel = 0.5
max_yaw = 0.5

pub = rospy.Publisher('/epos2/cmd_vel', Vector3, queue_size=10)


def cb_once(data):

    global init_fx
    init_fx = data.wrench.force.x
    sub_once.unregister()

global sub_once
sub_once = rospy.Subscriber("/netft_data",WrenchStamped,cb_once)

def filter(data,maximun,minimun):
    if abs(data) > maximun:
       return maximun
    elif abs(data) < minimun:
       return 0.0
    else:
       return data

def callback(data):
    range_fx = 5
    v_x = filter((data.wrench.force.x-init_fx)/range_fx,1,0.1)
    v_x = v_x*max_vel

    tmp = Vector(v_x,0,0)
    pub.publish(tmp)

if __name__ == '__main__':
    rospy.init_node('ft_control', anonymous=True)
    rospy.Subscriber("/force", WrenchStamped, callback)

    print "Start FT Control" 
    print "Initial fx =" + str(init_fx)
    rospy.spin()

