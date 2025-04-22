# 工具包使用与编译

## 标定IMU

标定imu的零偏和白噪声主要使用 `imu_utils`工具包，该工具包的编译需要依赖于 `code_utils`功能包，所以两个包不能同时在工作空间中使用 `catkin_make`来编译，最朴实的做法就是先将 `imu_utils`功能包压缩，使用 `catkin_make`编译工作空间，然后再解压 `imu_utils`，在使用 `catkin_make`编译一次即可。



## 相机标定

### kalibr安装

参考博客：[Ubuntu20.04安装kalibr-CSDN博客](https://blog.csdn.net/xiaojinger_123/article/details/121292803)

```shell
sudo apt update
sudo apt-get install python3-setuptools python3-rosinstall ipython3 libeigen3-dev libboost-all-dev doxygen libopencv-dev ros-noetic-vision-opencv ros-noetic-image-transport-plugins ros-noetic-cmake-modules python3-software-properties software-properties-common libpoco-dev python3-matplotlib python3-scipy python3-git python3-pip libtbb-dev libblas-dev liblapack-dev libv4l-dev python3-catkin-tools python3-igraph libsuitesparse-dev 
pip3 install wxPython
```

下载编译过程：

```shell
mkdir ~/kalibr_ws/src
cd ~/kalibr_ws/src
git clone --recursive https://github.com/ori-drs/kalibr

cd ~/kalibr_ws
source /opt/ros/noetic/setup.bash
catkin init
catkin config --extend /opt/ros/noetic
catkin config --merge-devel # Necessary for catkin_tools >= 0.4.
catkin config --cmake-args -DCMAKE_BUILD_TYPE=Release

catkin build -DCMAKE_BUILD_TYPE=Release -j4
```

使用过程：

```
source ~/kalibr_workspace/devel/setup.bash
rosrun kalibr kalibr_calibrate_cameras --bag Kalib_data_vga.bag --topics /zed2/zed_node/left/image_rect_color2 /zed2/zed_node/right/image_rect_color2 --models pinhole-radtan pinhole-radtan --target april.yaml
```




1
