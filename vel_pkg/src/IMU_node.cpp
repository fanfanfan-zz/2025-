#include<ros/ros.h>
#include<sensor_msgs/Imu.h>
#include<tf/tf.h>
#include<geometry_msgs/Twist.h>

ros::Publisher vel_pub;

void IMUcallback(const sensor_msgs::Imu msg)
{
// 检测消息包中四元数数据是否存在
    if(msg.orientation_covariance[0] < 0)
        return;
    // 四元数转成欧拉角
    tf::Quaternion quaternion(
        msg.orientation.x,
        msg.orientation.y,
        msg.orientation.z,
        msg.orientation.w
    );
    double roll, pitch, yaw;
    
    tf::Matrix3x3(quaternion).getRPY(roll, pitch, yaw);
    
    roll = roll*180/M_PI;
    pitch = pitch*180/M_PI;
    yaw = yaw*180/M_PI;
    //打印姿态信息
    ROS_INFO("滚转= %.0f 俯仰= %.0f 朝向= %.0f", roll, pitch, yaw);
    // 目标朝向角
    double target_yaw = 90;
    
    double diff_angle = target_yaw - yaw;

    geometry_msgs::Twist vel_cmd;
    vel_cmd.angular.z = diff_angle * 0.01;
    vel_cmd.linear.x = 0.1;
    vel_pub.publish(vel_cmd);


}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");   
    ros::init(argc, argv, "IMU_node");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/imu", 100, IMUcallback);
    
    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    
    ros::spin();
    return 0;
}
