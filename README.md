# 工具包使用与编译

## 标定IMU

标定imu的零偏和白噪声主要使用 `imu_utils`工具包，该工具包的编译需要依赖于 `code_utils`功能包，所以两个包不能同时在工作空间中使用 `catkin_make`来编译，最朴实的做法就是先将 `imu_utils`功能包压缩，使用 `catkin_make`编译工作空间，然后再解压 `imu_utils`，在使用 `catkin_make`编译一次即可。

## 编译中遇到的问题

### code_utils与imu_utils联合编译

**报错1**：

```shell
Could not find a package configuration file provided by “code_utils” with
any of the following names:
code_utilsConfig.cmake
code_utils-config.cmake
```

解决方案：[imu_utils协方差标定包编译](https://blog.csdn.net/m0_38144614/article/details/116293420)，本质上就是现将imu包压缩起来，单独编译code包

**报错2**：

```shell
: fatal error: backward.hpp: 没有那个文件或目录     2 | #include "backward.hpp"
```

这里是缺少了一个cpp的库文件，安装该文件参考：[backwaer.cpp安装](https://zhuanlan.zhihu.com/p/397148839).具体的安装操作为：

```shell
sudo apt-get install libdw-dev
wget https://raw.githubusercontent.com/bombela/backward-cpp/master/backward.hpp
sudo mv backward.hpp /usr/include
```

**报错3**：一批CV库中的宏名称问题：
OpenCV 3.0及以上版本中，`CV_LOAD_IMAGE_UNCHANGED` 和 `CV_LOAD_IMAGE_GRAYSCALE` 已被弃用，应该使用 `IMREAD_UNCHANGED` 和 `IMREAD_GRAYSCALE`。`CV_MINMAX` 已被弃用，应该使用 `NORM_MINMAX`。

### imu_utils继续编译

**报错1**：

```cpp
/home/vulcan/personLibs/cam_cali_tools/src/imu_utils/src/imu_an.cpp:68:19: error: aggregate ‘std::ofstream out_t’ has incomplete type and cannot be defined
   68 |     std::ofstream out_t;
      |                   ^~~~~
/home/vulcan/personLibs/cam_cali_tools/src/imu_utils/src/imu_an.cpp:69:19: error: aggregate ‘std::ofstream out_x’ has incomplete type and cannot be defined
   69 |     std::ofstream out_x;
      |                   ^~~~~
/home/vulcan/personLibs/cam_cali_tools/src/imu_utils/src/imu_an.cpp: In function ‘void writeData3(std::string, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&, const std::vector<double>&)’:
/home/vulcan/personLibs/cam_cali_tools/src/imu_utils/src/imu_an.cpp:90:19: error: aggregate ‘std::ofstream out_t’ has incomplete type and cannot be defined
   90 |     std::ofstream out_t;
      |                   ^~~~~
/home/vulcan/personLibs/cam_cali_tools/src/imu_utils/src/imu_an.cpp:91:19: error: aggregate ‘std::ofstream out_x’ has incomplete type and cannot be defined
   91 |     std::ofstream out_x;
      |                   ^~~~~
/home/vulcan/personLibs/cam_cali_tools/src/imu_utils/src/imu_an.cpp:92:19: error: aggregate ‘std::ofstream out_y’ has incomplete type and cannot be defined
   92 |     std::ofstream out_y;
      |                   ^~~~~
/home/vulcan/personLibs/cam_cali_tools/src/imu_utils/src/imu_an.cpp:93:19: error: aggregate ‘std::ofstream out_z’ has incomplete type and cannot be defined
   93 |     std::ofstream out_z;
```

解决方案，在报错的cpp文件开头补充库文件引用：

```cpp
#include <fstream>
#include <vector>
#include <string>
```

## camera_tools工具包

编写了一个简易的可以捕获ros中 `sensor_msgs::Image`类型的图像数据的工具包，用于直接接收相机ros节点发出的图像数据，并可以使用按键控制进行图像保存。
