#include "img_capture.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "img_capture_node");
    ros::NodeHandle nh;
    IMG_CAPTURE img_capture(&nh);
    ros::Rate loop_rate(30);
    char key = 0;
    while (ros::ok())
    {
        key = img_capture.showImage();
        if(key == 'q'){
            std::cout << "exit" << std::endl;
            break;
        }
        ros::spinOnce();
    }
    return 0;
}


