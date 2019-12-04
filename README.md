# epos2

maxon DC motor current control, communicate with rospy

## Protocal

Torque.srv

	float64 position # used as step counter
	float64 torque
	int16 init # if true, the controller random init a state
	---
	float64[3] state_new # cos() sin() velocity
	float64 reward #used
	bool done # used
	float64 velocity # not used, calc by differenciate position
	float64 position_new #-pi to pi, now not used
	float64 current # not used

## EPOS2 info

using USB mode, no need to set baudrate

for EPOS2 setup for linux, see docs/EPOS Command Library.pdf

for driver and library, find 'EPOS_Linux_Library' on maxon official site(https://www.maxonmotorusa.com/maxon/view/product/control/Positionierung/347717)

- g_usNodeId = 1;
- g_deviceName = "EPOS2";
- g_protocolStackName = "MAXON SERIAL V2";
- g_interfaceName = "USB";
- g_portName = "USB0";


## Files

### src

velocity_pub.cpp: node for controlling velocity.

wrap.cpp: wrap api to make code clean and easy to program

### include

headings

## Usages

use as a ros package, put the whole epos2 files under workspace/src and compile with catkin

	#under ${workspace}
	catkin_make
	rosrun epos2 velocity_pub
	code will prompt for input

## Benchmark

time taken:

- write position: **9ms**
- write current: **5ms**
- get current: **5ms**
- get position: **5ms**
- get velocity: **5ms**
- ros send request immediately after get response: **7ms**(from the perspective of server)
- rl get action: **<=3ms**
- rl update & pull: **<=4ms**

- get all 3 parameter takes about **14ms** on average

- rosservice + choose_action + update <= 14ms

now strategy: 	get position 5ms, calculate velocity based on position, get request & return reward 7ms, 
				rl get action <=3ms, rl update & pull <=4ms

controlling cycle: 30ms, 33.3Hz
