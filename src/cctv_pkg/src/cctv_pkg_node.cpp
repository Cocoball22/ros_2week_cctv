#include <ros/ros.h>
// 이미지 전송을 위한 ROS 패키지 헤더
#include <image_transport/image_transport.h>
// OpenCV 화면 출력 등을 위한 헤더
#include <opencv2/highgui/highgui.hpp>
// ROS 이미지 메시지와 OpenCV 이미지 간의 변환을 위한 헤더
#include <cv_bridge/cv_bridge.h>
// ROS 이미지 메시지 타입 헤더
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CompressedImage.h>

class Comp_Sub{
private:
    ros::NodeHandle nh;
    // 이미지 구독자 객체
    ros::Subscriber Comp_sub_;

public:
    Comp_Sub()
    {
        // camera/color/image_raw 토픽을 받아 이미지
        Comp_sub_ = nh.subscribe("/camera/color/image_raw",10,&Comp_Sub::imageCb,this);
    }

// 이미지를 영상으로 부터 수신하는 서브스크라이버 sensor_mags/image를 통해서 값을
    void imageCb(const sensor_msgs::ImageConstPtr& msg)
    {
        try
        {
            //cv_bridge를 사용하여 ROS 이미지 메시지를 OpenCV 이미지로 변환
            //bgr8 형식으로 변환하여 처리
            cv::imshow("RGB Image", cv_bridge::toCvShare(msg, "bgr8")->image);
            cv::waitKey(30);
        }
        catch(const std::exception& e)
        {
            // 이미지 변환 실패 시 에러 메시지 출력
            // 현재 인코딩 형식을 포함하여 에러 메시지 표시
            ROS_ERROR("Could not convert from '%s' to 'bgr8.", msg->encoding.c_str());
        }
    }
    
};

int main(int argc, char** argv)
{
    // ROS 노드 초기화
    // 노드 이름을 "Comp_Pub"로 설정
    ros::init(argc, argv, "cctv_pkg_node");
    
    // Comp_Sub 클래스의 인스턴스 생성
    Comp_Sub Comp_Sub__;

    // ROS 메시지 루프 실행
    // 모든 콜백 함수들이 호출될 수 있도록 대기 
    ros::spin();

}