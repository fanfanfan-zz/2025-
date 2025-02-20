#!/usr/bin/env python3  

import rospy  
from add_two_ints_service.srv import AddTwoInts, AddTwoIntsRequest  

def add_two_ints_client(x, y):  
    rospy.wait_for_service('add_two_ints')  
    try:  
        add_two_ints = rospy.ServiceProxy('add_two_ints', AddTwoInts)#向service发送请求，并建立一个add_two_ints用来承载服务端所返回的响应信息  
        req = AddTwoIntsRequest()  #使用消息包类型AddTwoIntsRequest
        req.a = x  #建立两个整数
        req.b = y  
        resp1 = add_two_ints(req) #调用代理add_two_ints来发送请求消息包（req）并获取响应 
        return resp1.sum #定义add_two_ints_client(x, y)函数的返回值为resp1.sum
    except rospy.ServiceException as e:  
        print("Service call failed: %s"%e)  

if __name__ == "__main__":  
    rospy.init_node('add_two_ints_client')  #初始化节点
    x = 3  #向req.a、req.b发送两个整数3、5
    y = 5  
    rospy.loginfo("Requesting %s+%s"%(x, y))#打印文字提示  
    sum = add_two_ints_client(x, y)  
    rospy.loginfo("%s + %s = %s"%(x, y, sum))
