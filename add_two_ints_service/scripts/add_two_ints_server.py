#!/usr/bin/env python3  

import rospy  
from add_two_ints_service.srv import AddTwoInts, AddTwoIntsResponse  

def handle_add_two_ints(req):  
    rospy.loginfo("Returning [%s + %s = %s]"%(req.a, req.b, (req.a + req.b)))#文字提示  
    return AddTwoIntsResponse(req.a + req.b)  #返回值sum

def add_two_ints_server():  
    rospy.init_node('add_two_ints_server') #初始化节点 
    s = rospy.Service('add_two_ints', AddTwoInts, handle_add_two_ints)  
    rospy.loginfo("Ready to add two ints.")  
    rospy.spin()  

if __name__ == "__main__":  
    add_two_ints_server()
