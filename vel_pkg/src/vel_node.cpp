#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

/*
这是一个简单的ROS节点，用于发布速度命令。
我通过这个程序来进一步熟悉ros的发布机制，向/cmd_vel话题发布Twist消息包以控制机器人运动。
另外这个代码还待进一步完善，比如结束该程序后将机器人速度恢复为0。
*/
int main(int argc, char *argv[])
{
    ros::init(argc ,argv , "vel_node");

    ros::NodeHandle nh;
    ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel",10);
    ros::Rate loop_rate(1); //设置循环频率为1Hz

    geometry_msgs::Twist vel_msg; //定义一个Twist类型的消息,命名为vel_msg
    vel_msg.linear.x = 0.2;
    vel_msg.linear.y = 0;
    vel_msg.linear.z = 0;
    vel_msg.angular.x = 0;
    vel_msg.angular.y = 0;
    vel_msg.angular.z = 0.2;

    while (ros::ok())
    {
        vel_pub.publish(vel_msg);
        loop_rate.sleep();
    }
    
    return 0;
}
