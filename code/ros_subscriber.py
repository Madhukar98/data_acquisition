#! /usr/bin/env python

import rospy
from std_msgs.msg import String
from std_msgs.msg import Int32
import time
import pandas as pd
import numpy as np

col1=[]
col2=[]
col3=[]
col4=[]
t2=0

def callback(msg):
    s = msg.data
    curr = ""
    val = []
    for char_index in range(len(s)):
        if(s[char_index] != ' '):
            curr = curr + s[char_index]
        else:
            val.append(int(curr))
            curr = ""

def callback1(msg):
	global col1
	global t2
	s = msg.data
	col1.append(s)
	t2 = max(rospy.get_time(),t2)

def callback2(msg):
	global col2
	global t2
	s = msg.data
	col2.append(s)
	t2 = max(rospy.get_time(),t2)

def callback3(msg):
	global col3
	global t2
	s = msg.data
	col3.append(s)
	t2 = max(rospy.get_time(),t2)

def callback4(msg):
	global col4
	global t2
	s = msg.data
	col4.append(s)
	t2 = max(rospy.get_time(),t2)

if __name__ == "__main__":

	rospy.init_node("python_script", anonymous = False)
	q = 100
	t1 = rospy.get_time()

	rospy.Subscriber("myTopic", String, callback)
	rospy.Subscriber("value1", Int32, callback1)
	rospy.Subscriber("value2", Int32, callback2)
	rospy.Subscriber("value3", Int32, callback3)
	rospy.Subscriber("value4", Int32, callback4)
	while(True):
		if(t2-t1>60):
			t1=t2
			x=min(len(col1),len(col2),len(col3),len(col4))
			col1=col1[:x]
			col2=col2[:x]
			col3=col3[:x]
			col4=col4[:x]
			df=pd.DataFrame({"A": col1,"B": col2,"C": col3,"D": col4})
			df.to_csv("data.csv", index=False)
			col1.clear()
			col2.clear()
			col3.clear()
			col4.clear()

	rospy.spin()