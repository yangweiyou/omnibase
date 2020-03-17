#!/usr/bin/env python
import rospy
import time
from geometry_msgs.msg import WrenchStamped 
from geometry_msgs.msg import Vector3
from geometry_msgs.msg import Twist

max_vel = 0.5
max_yaw = 0.5

pub = rospy.Publisher('/omnibase/cmd_vel', Twist, queue_size=10)


def cb_once(data):

    global init_fx
    init_fx = data.wrench.force.x
    global init_fy
    init_fy = data.wrench.force.y
    global init_fz
    init_fz = data.wrench.force.z
    global init_tx
    init_tx = data.wrench.torque.x
    global init_ty
    init_ty = data.wrench.torque.y
    global init_tz
    init_tz = data.wrench.torque.z
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
    range_fx = 10
    v_x = filter((data.wrench.force.x-init_fx)/range_fx,1,0.1)
    v_x = -v_x*max_vel

    range_fy = 10
    v_yaw = filter((data.wrench.force.y-init_fy)/range_fy,1,0.1)
    v_yaw = v_yaw*max_yaw

    tmp = Twist()
    tmp.linear = Vector3(v_x, v_yaw, 0)
    tmp.angular = Vector3(0, 0 , 0)

    pub.publish(tmp)

if __name__ == '__main__':
    rospy.init_node('ft_control', anonymous=True)
    rospy.Subscriber("/netft_data", WrenchStamped, callback)

    print "Start FT Control" 
    print "Initial fx =" + str(init_fx)
    print "Initial fy =" + str(init_fy)
    rospy.spin()
