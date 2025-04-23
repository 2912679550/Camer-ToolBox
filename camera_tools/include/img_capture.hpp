#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <opencv2/opencv.hpp>
#include "public_param.hpp"
#include <cv_bridge/cv_bridge.h>
#include <string>
#include <iostream>

class IMG_CAPTURE{
public:
    IMG_CAPTURE(ros::NodeHandle* nh);
    ~IMG_CAPTURE();

    cv::Mat cur_img_;
    cv::Mat last_img_;

    void saveImage();
    char showImage();

private:
    ros::Subscriber image_sub;
    ros::NodeHandle* nh_;

    // todo 图形话题参数
    int image_width_ = 640;
    int image_height_ = 480;
    float image_hz_ = 30.0;

    std::string image_topic_name_ = "/camera/image_raw";
    std::string save_path_ = "/home/yangchen/catkin_ws/src/robot_tools/camera_tools/image/";
    void imageCallback(const sensor_msgs::ImageConstPtr& msg);
};
