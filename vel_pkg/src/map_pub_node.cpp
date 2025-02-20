#include<ros/ros.h>
#include<nav_msgs/OccupancyGrid.h>


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "map_pub_node");
    ros::NodeHandle nh;
    // 发布一个话题，话题名为map，消息类型为map_msgs::OccupancyGrid，队列长度为10
    ros::Publisher map_pub = nh.advertise<nav_msgs::OccupancyGrid>("map", 10);

    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        // 创建并设置map消息包的参数
        nav_msgs::OccupancyGrid map;
        
        map.header.stamp = ros::Time::now();
        map.header.frame_id = "map";
        
        map.info.resolution = 1.0;
        map.info.width = 4;
        map.info.height = 2;
        map.info.origin.position.x = 0;
        map.info.origin.position.y = 0;
        
        map.data.resize(map.info.width * map.info.height);
        map.data[0] = 100;
        map.data[1] = 100;
        map.data[2] = 0;
        map.data[3] = -1;

        // 发布map消息
        map_pub.publish(map);
        loop_rate.sleep();
    }
    return 0;
}
