#include "img_capture.hpp"

IMG_CAPTURE::IMG_CAPTURE(ros::NodeHandle* nh)
{
    if(nh == nullptr)
    {
        std::cout << BLOD_STRING
                    << RED_STRING
                    << "img_capture constructor error: nh_ is nullptr"
                    << RESET_STRING
                    << std::endl;
        return;
    }else{
        nh_ = nh;
    }
    nh_->param<std::string>("img_topic", image_topic_name_, "default_robot");
    nh_->param<int>("img_width", image_width_, 640);
    nh_->param<int>("img_height", image_height_, 480);
    nh_->param<float>("img_hz", image_hz_, 30.0);
    nh_->param<std::string>("save_path", save_path_, "");
    image_sub = nh_->subscribe(image_topic_name_, 1, &IMG_CAPTURE::imageCallback, this);
}

IMG_CAPTURE::~IMG_CAPTURE(){

};

void IMG_CAPTURE::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    cv::Mat image;
    try
    {
        image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }
    
    cv::resize(image, image, cv::Size(image_width_, image_height_));
    last_img_ = cur_img_.clone();
    cur_img_ = image.clone();
}

void IMG_CAPTURE::saveImage()
{
    static int startID = 0;
    std::string file_name = save_path_ + "/image_" + std::to_string(startID) + ".png";
    cv::imwrite(file_name, cur_img_);
    startID++;
}

char IMG_CAPTURE::showImage(){
    if(cur_img_.empty())
    {
        std::cout << "No image received yet." << std::endl;
        return 0;
    }
    cv::imshow("image", cur_img_);
    char key = cv::waitKey(1.0 / image_hz_ * 1000);
    if (key == 27) // ESC key
    {
        std::cout << "ESC key pressed. Exiting..." << std::endl;
        return key;
    }
    else if (key == 's') // 's' key
    {
        saveImage();
        std::cout << "Image saved." << std::endl;
    }
    else if (key == 'c') // 'c' key
    {
        std::cout << "Image captured." << std::endl;
    }
    else if (key == 'q') // 'q' key
    {
        std::cout << "Quit key pressed. Exiting..." << std::endl;
    }
    return key;
}



