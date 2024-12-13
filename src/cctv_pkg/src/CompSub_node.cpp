#include <ros/ros.h>
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
    ros::Subscriber Comp_raw_sub;

public:
    Comp_Sub()
    {
        Comp_raw_sub = nh.subscribe("/camera/color/image_raw",10,&Comp_Sub::imageCb,this);
        // camera/color/image_raw 토픽을 받아 이미지
        Comp_sub_ = nh.subscribe("/compressed", 10, &Comp_Sub::imageCallback, this);
    }

// 이미지를 영상으로 부터 수신하는 서브스크라이버 sensor_mags/image를 통해서 값을
// image_raw는 imageConstPtr 
    void imageCb(const sensor_msgs::ImageConstPtr& msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            cv::imshow("Raw Image", cv_bridge::toCvShare(msg,"bgr8") -> image);
            cv::waitKey(1);
        }
        catch(cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
        }
    }

     void imageCallback(const sensor_msgs::CompressedImage::ConstPtr& msg) // compressedImage 압축된 이미지
     {
      // 예외가 발생할 수 있는 코드 블록을 중괄호{}로 감싸 준다.
       try
       {  
          cv::Mat frame = cv::imdecode(cv::Mat(msg->data), cv::IMREAD_COLOR); // decode과정을 해줘야함
          // bit_dipth unsigned channel 1
          cv::Mat inverted_frame = cv::Mat::zeros(frame.size(), CV_8UC1);

          // 이미지 데이터를 순화하면서 역상 변환
          for (int y = 0; y < frame.rows; y++)
          {
            for(int x = 0; x < frame.cols; x++)
            {
              cv::Vec3b& pixel_bgr = frame.at<cv::Vec3b>(y, x);  // 8-bit unsigned, 3채널 (BGR 이미지) 
              uchar& pixel_gray = inverted_frame.at<uchar>(y, x); // unsigned char
          
              pixel_gray = (pixel_bgr[0] * 0.114) + (pixel_bgr[1] * 0.587) + (pixel_bgr[2] * 0.299);
            }
          }
        //  ROS_INFO("size: %d",frame.rows);

        // 이미지 표시
         cv::imshow("Compressed Image", frame);
         cv::imshow("Gray Image", inverted_frame);
         cv::waitKey(1); // 입력 키를 기다리는 함수이며 ms단위
         
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
    ros::init(argc, argv, "CompSub_node");
    
    // Comp_Sub 클래스의 인스턴스 생성
    Comp_Sub Comp_Sub__;
    
    // ROS 메시지 루프 실행
    // 모든 콜백 함수들이 호출될 수 있도록 대기 
    ros::spin();

}