#include <ros/ros.h>
#include <stdio.h>
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
    cv::Mat frame, data ; // OpenCV의 기본 이미지 매트릭스 형식

public:
    Comp_Sub()
    {
        // camera/color/image_raw 토픽을 받아 이미지
        Comp_sub_ = nh.subscribe("/compressed", 10, &Comp_Sub::imageCallback, this);
    }
    ~Comp_Sub()
    {

    }

// // 이미지를 영상으로 부터 수신하는 서브스크라이버 sensor_mags/image를 통해서 값을
// // image_raw는 imageConstPtr 
//     void imageCb(const sensor_msgs::CompressedImage& msg)
//     {
//         cv_bridge::CvImagePtr cv_ptr;
        
//         try
//         {
//             std::cout << "this is working" << std::endl;
//             // cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);

//             img = cv::imdecode();
            
//         }
//         catch(cv_bridge::Exception& e)
//         {
//             ROS_ERROR("cv_bridge exception: %s", e.what());
//         }
//         cv::imshow("window", );
//         cv::waitKey(10);
//     }
    
     void imageCallback(const sensor_msgs::CompressedImage::ConstPtr& msg) // compressedImage 압축된 이미지
     {
       try
       {  // 예외가 발생할 수 있는 코드 블록을 중괄호{}로 감싸 준다.
          // 압축된 이미지 데이터를 cv::Mat으로 변환
          frame = cv::imdecode((msg->data), 1); // decode과정을 해줘야함 

        // 이미지 표시
         cv::imshow("view", frame);
         cv::waitKey(1); // 입력 키를 기다리는 함수??
       }
       catch (cv_bridge::Exception& e)
       {
        // 예외가 발생하면 다음 문장을 실행
         ROS_ERROR("cannot decode image");
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