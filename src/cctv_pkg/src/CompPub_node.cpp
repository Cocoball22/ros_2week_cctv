#include <ros/ros.h>
#include "test.pkg/test_msg.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "CompPub_node");
    ros::NodeHandle nh;

    ros::Publisher Com_pub = nh.advertise<test_pkg::test_msg>("/chatter", 100);

    ros:Rate loop_rate(10);

    test_pkg::test_msg msg;

    while(ros::ok())
    {
        msg.stamp = ros::Time::now();
        msg.data = count;

        ROS_INFO("send time(sec) = %d", msg.stamp.sec);
        ROS_INFO("send msg = %d", msg.data)

        Com_pub.publish(msg);
        loop_rate.sleep();
        ++count
    }
    retrun 0;
}