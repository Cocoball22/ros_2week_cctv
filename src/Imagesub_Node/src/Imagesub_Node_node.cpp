#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>

class Imagesub_Node{
private:
    ros::NodeHandle nh;
    ros::Subscriber image_sub;

public:
    Imagesub_Node()
    {
        image_sub = nh.subscribe("/camera/color/image_raw",10,&Imagesub_Node::Subscriber_image,this);


    }

    void Subscriber_image(const sensor_msgs::ImageConstPtr& msg)
    {
        try
        {
            cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
            cv::waitKey(30);
        }
        catch(const std::exception& e)
        {
            ROS_ERROR("Could not convert from '%s' to 'bgr8.", msg->encoding.c_str());
        }
    }
    
};

int main(int argc, char** argv)
{
    
    ros::init(argc, argv, "Imagesub_Node");
    
    Imagesub_Node Imagesub_Node_;

    ros::spin();

}
