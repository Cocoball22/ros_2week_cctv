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
    sensor_msgs::Image img;
    std_msgs::Header header;

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
    
    /*header: 
         seq: 8816
         stamp: 
           secs: 1733966737
           nsecs:  22661888
         frame_id: "camera_color_optical_frame"
         height: 480
         width: 640
         encoding: "rgb8"
         is_bigendian: 0
         step: 1920
         data: "<array type: uint8, length: 921600>"
     */

    /*
    header: 
      seq: 2077
      stamp: 
        secs: 0
        nsecs:         0
      frame_id: ''
      format: ''
      data: "<array type: uint8, length: 35777>"

    */

     void imageCallback(const sensor_msgs::CompressedImage::ConstPtr& msg) // compressedImage 압축된 이미지
     {
 
        // ROS_INFO("Timestamp:");
        // ROS_INFO("  - secs: %d", msg->header.stamp.sec);
        // ROS_INFO("  - nsecs: %d", msg->header.stamp.nsec);

        // 2. Frame ID 분석
        // ROS_INFO("Frame ID: %s", msg->header.frame_id.c_str());

        // 3. Format 분석
        // ROS_INFO("Format: %s", msg->format.c_str());

        // 4. 데이터 크기 정보 (선택적)
        // ROS_INFO("Data size: %lu bytes", msg->data.size());

        // 시간 차이 계산 (현재 시간과 메시지 시간의 차이)
        // ros::Time current_time = ros::Time::now();
        // ros::Duration diff = current_time - msg->header.stamp;
        // ROS_INFO("Time difference from now: %.3f seconds", diff.toSec());

        // ROS_INFO("-------------------");

        // 기본적인 이미지 정보 출력
        // ROS_INFO_STREAM("Image properties:");
        // ROS_INFO_STREAM("Size: " << frame.rows << "x" << frame.cols);
        // ROS_INFO_STREAM("Channels: " << frame.channels());
        // ROS_INFO_STREAM("Type: " << frame.type());

       try
       {  // 예외가 발생할 수 있는 코드 블록을 중괄호{}로 감싸 준다.
          // 압축된 이미지 데이터를 cv::Mat으로 변환
          frame = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR); // decode과정을 해줘야함
          
          cv::Mat inverted_frame = cv::Mat::zeros(frame.size(), CV_8UC1);

          // 이미지 데이터를 순화하면서 역상 변환
          for (int y = 0; y < frame.rows; y++)
          {
            for(int x = 0; x < frame.cols; x++)
            {
              cv::Vec3b& pixel_1 = frame.at<cv::Vec3b>(y, x);  // 8-bit unsigned, 3채널 (BGR 이미지) 
              uchar& pixel_2 = inverted_frame.at<uchar>(y, x); // unsigned char

              // pixel_2[0] = 255 - pixel_1[0]; // B
              // pixel_2[1] = 255 - pixel_1[1]; // G
              // pixel_2[2] = 255 - pixel_1[2]; // R
              // pixel_2[0] = B, pixel_2[1] = G, pixel_2[2] = R
              pixel_2 = (pixel_1[0] * 0.114) + (pixel_1[1] * 0.587) + (pixel_1[2] * 0.299);
            }
          }
        //  ROS_INFO("size: %d",frame.rows);

        // 이미지 표시
         cv::imshow("Original Image", frame);
         cv::imshow("Inverted Image", inverted_frame);
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