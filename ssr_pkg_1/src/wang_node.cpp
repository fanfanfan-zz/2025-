#include <ros/ros.h>
#include <std_msgs/String.h>  

/* 
这串代码是看完阿杰的b站视频“年轻人的第一个node节点”与“publisher发布者的c++实现”写的
另外为了控制打印的间隔时间，我还学习并比较了ros中的ros::Rate和ros::Duration两个函数，发现ros::Rate的精度更高，所以最终选择了ros::Rate
另外还学会了初始化节点，编写cmake文件
编写ros中的while循环结构，以及如何使用ros::Publisher发布消息
学习如何使用std_msgs::String消息类型的消息包
学习了ros：：NodeHandle类，以及如何使用advertise函数发布消息
 */

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "wang_node");
    ros::NodeHandle nh; 
      
    
    printf("开始报数！\n");   
    
    ros::Publisher string_pub = nh.advertise<std_msgs::String>("first_topic_chatter", 10); 
    ros::Rate loop_rate(1); 

    while (ros::ok())
    {
        printf("topic,启动!\n");
        std_msgs::String msg;//定义一个string类型的消息，命名为msg
        msg.data = "开始向topic聊天群发消息了!";//给msg赋值
        string_pub.publish(msg);//发布消息
        loop_rate.sleep();  
    }
    
    return 0;
}
