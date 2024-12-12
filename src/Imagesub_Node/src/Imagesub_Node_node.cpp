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

class Imagesub_Node{
private:
    ros::NodeHandle nh;
    // 이미지 구독자 객체
    ros::Subscriber image_sub_;
    // 이미지 퍼블리셔 객체
   ros::Publisher image_compressed_pub_;

    image_transport::Publisher image_pub_;

    cv::Mat src;
    
    bool val;
public:
    Imagesub_Node()
    {
        // camera/color/image_raw 토픽을 받아 이미지
        image_sub_ = nh.subscribe("/camera/color/image_raw",10,&Imagesub_Node::imageCb,this);
        // 압축된 이미지로 전송 rostopic에서 보내는 데이터값과 내가 토픽에서 보내는 데이터
        
        // sensor_msg 데이터 타입으로 토픽 메시지는 "/compressed" 
        image_compressed_pub_ = nh.advertise<sensor_msgs::CompressedImage>("/compressed",10);
    }

// 이미지를 영상으로 부터 수신하는 서브스크라이버 sensor_mags/image를 통해서 값을
    // void Subscriber_image(const sensor_msgs::ImageConstPtr& msg)
    // {
    //     try
    //     {
    //         //cv_bridge를 사용하여 ROS 이미지 메시지를 OpenCV 이미지로 변환
    //         //bgr8 형식으로 변환하여 처리
    //         cv::imshow("RGB Image", cv_bridge::toCvShare(msg, "bgr8")->image);
    //         cv::waitKey(30);
    //     }
    //     catch(const std::exception& e)
    //     {
    //         // 이미지 변환 실패 시 에러 메시지 출력
    //         // 현재 인코딩 형식을 포함하여 에러 메시지 표시
    //         ROS_ERROR("Could not convert from '%s' to 'bgr8.", msg->encoding.c_str());
    //     }
    // }
    
    void imageCb(const sensor_msgs::ImageConstPtr& msg)
   {
     cv_bridge::CvImagePtr cv_ptr;
     sensor_msgs::CompressedImage compressed_msg;
     try
     {
        // BGR8은 색상이 올바름, RGB8은 색상이 파란느낌, mono8은 grayscale은 아닌듯한데 gray가나옴
        // 포인터 cv_ptr 
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        src = cv_ptr -> image.clone();

        // 여기서 bool로 사용한 이유는 값이 변하는지 안 변하는지를 확인 하는 변수
       val = cv::imencode(".jpg", src, compressed_msg.data); // 행렬의 타입은 mat이고 이걸 토픽으로 아웃풋을 만들어서 val에 대입

        // 인코딩에서 compressed에 대한 설정을 하지 않았다 
        // 현재 ROS 시간으로 타임스탬프 설정
        //compressed_msg.header.stamp = ros::Time::now();
        compressed_msg.header = msg->header;
        compressed_msg.header.frame_id =  "camera_compressed_image"; // 프레임 ID설정
        compressed_msg.format = "my:rgb8; jpeg compressed bgr8"; // 메시지의 데이터 및 포맷 설정
        

        
     }
     catch (cv_bridge::Exception& e)
     {
       ROS_ERROR("cv_bridge exception: %s", e.what());
       return;
     }
 
     // Update GUI Window
     cv::imshow("OPENCV_WINDOW", cv_ptr->image);
     cv::waitKey(3);
 
 
     // Output modified video stream
     //image_compressed_pub_.publish(cv_ptr->toImageMsg());

     // val은 변환이 되었는지를 확인하는 변수
        // if(val == true)
        // ROS_INFO("complete encode");
        image_compressed_pub_.publish(compressed_msg);

   }
};

int main(int argc, char** argv)
{
    // ROS 노드 초기화
    // 노드 이름을 "Imagesub_Node"로 설정
    ros::init(argc, argv, "Imagesub_Node");
    
    // Imagesub_Node 클래스의 인스턴스 생성
    Imagesub_Node Imagesub_Node_;

    // ROS 메시지 루프 실행
    // 모든 콜백 함수들이 호출될 수 있도록 대기 
    ros::spin();

}
