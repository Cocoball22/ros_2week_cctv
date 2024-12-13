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
#include <stdexcept>

class ImageSub_node{
private:
    ros::NodeHandle nh;
    // 이미지 구독자 객체
    ros::Subscriber image_sub_;
    // 이미지 퍼블리셔 객체
    ros::Publisher image_compressed_pub_;
public:
    ImageSub_node()
    {
        // camera/color/image_raw 토픽을 받아 이미지
        image_sub_ = nh.subscribe("/camera/color/image_raw",10,&ImageSub_node::imageCb,this);
        // 압축된 이미지로 전송 rostopic에서 보내는 데이터값과 내가 토픽에서 보내는 데이터
        
        // sensor_msg 데이터 타입으로 토픽 메시지는 "/compressed" 
        image_compressed_pub_ = nh.advertise<sensor_msgs::CompressedImage>("/compressed",10);
    }
    
    void imageCb(const sensor_msgs::ImageConstPtr& msg)
   {
      // 이미지의 구조체의 포인터 - ROS 이미지 데이터를 읽기 및 쓰기 가능한 OpenCV 데이터로 변환
      cv_bridge::CvImagePtr cv_ptr;
      // 압축된 이미지 데이터 
      sensor_msgs::CompressedImage compressed_msg;
      compressed_msg.header = msg->header;
      compressed_msg.header.frame_id =  "camera_compressed_image"; // 프레임 ID설정
      compressed_msg.format = "jpeg"; // 메시지의 데이터 및 포맷 설정

     try
     {
        // BGR8은 색상이 올바름, RGB8은 색상이 파란느낌, mono8은 grayscale은 아닌듯한데 gray가나옴
        // 포인터 cv_ptr로 이미지
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        cv::Mat src = cv_ptr -> image.clone(); // image

        // 여기서 bool로 사용한 이유는 값이 변하는지 안 변하는지를 확인 하는 변수
       cv::imencode(".jpg", src, compressed_msg.data); // 행렬의 타입은 mat이고 이걸 토픽으로 아웃풋을 만들어서 val에 대입        
       cv::imshow("OPENCV_WINDOW", cv_ptr->image);
      
       cv::waitKey(1);
     }
     catch (cv_bridge::Exception& e)
     {
       ROS_ERROR("cv_bridge exception: %s", e.what());
     }
     image_compressed_pub_.publish(compressed_msg);
   }
};

int main(int argc, char** argv)
{
    // ROS 노드 초기화
    // 노드 이름을 "Imagesub_Node"로 설정
    ros::init(argc, argv, "ImageSub_node");
    
    // Imagesub_Node 클래스의 인스턴스 생성
    ImageSub_node ImageSub_node_;

    // ROS 메시지 루프 실행
    // 모든 콜백 함수들이 호출될 수 있도록 대기 
    ros::spin();

}
