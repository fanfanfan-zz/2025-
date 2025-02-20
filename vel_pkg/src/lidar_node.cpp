#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
/*


*/
ros::Publisher vel_pub;
int nCount = 0;
void lidarCallback(const sensor_msgs::LaserScan msg)
{
    float mid_range = msg.ranges[180];
    
    ROS_INFO(" 前方测距为: %f 米", mid_range);

    if(nCount > 0)
    {
        nCount--;
        return;
    }


    geometry_msgs::Twist vel_cmd;
    if (mid_range < 1.5)
    {
        vel_cmd.angular.z = 0.3;
        nCount = 50;
    }
    else
    {
        vel_cmd.linear.x = 0.1;
    }
   vel_pub.publish(vel_cmd);

}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "zh_CN.UTF-8");
    ros::init(argc, argv, "lidar_node");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("/scan", 10, lidarCallback);
    
    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::spin();
    return 0;
}
