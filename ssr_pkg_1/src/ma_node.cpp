#include <ros/ros.h>
#include <std_msgs/String.h>

/*
这个程序是一个简单的ROS节点，它订阅一个名为“chatter”的话题，并打印出接收到的消息。
我通过这个程序来熟悉ROS的基本操作，包括创建节点、订阅话题、处理消息、构建回调函数。
另外我还了解到在写回调函数时使用std_msgs::String::Ptr msg，可以避免在回调函数中创建新的消息对象，从而提高程序的效率。
*/



void chatterCallback(const std_msgs::String::Ptr& msg)
{
    printf("I heard: [%s]\n", msg->data.c_str());
}

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "ma_node");

    ros::NodeHandle nh;

    ros::Subscriber string_sub = nh.subscribe("first_topic_chatter", 10, chatterCallback);

    while (ros::ok())
    {
        ros::spin();
    }
    

    return 0;
}
