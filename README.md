# 工具包使用与编译

## 工具包编译

kalibr参考博客：[Ubuntu20.04安装kalibr-CSDN博客](https://blog.csdn.net/xiaojinger_123/article/details/121292803)

由于整合了kalibr，所以需要使用 `catkin build`进行编译，整合后在工作空间下需要执行的编译流程为：

```shell
catkin init
catkin config --extend /opt/ros/noetic
catkin config --merge-devel # Necessary for catkin_tools >= 0.4.
catkin config --cmake-args -DCMAKE_BUILD_TYPE=Release

catkin build -DCMAKE_BUILD_TYPE=Release -j4
```

在src中我也预留了一个供编译用的脚本，在工作空间根目录执行 `./src/autoBuild.sh`即可。

## 标定IMU

标定imu的零偏和白噪声主要使用 `imu_utils`工具包，该工具包的编译需要依赖于 `code_utils`功能包，所以两个包不能同时在工作空间中使用 `catkin_make`来编译，最朴实的做法就是先将 `imu_utils`功能包压缩，使用 `catkin_make`编译工作空间，然后再解压 `imu_utils`，在使用 `catkin_make`编译一次即可。

## 相机标定

### 使用过程：

```
source ~/kalibr_workspace/devel/setup.bash
rosrun kalibr kalibr_calibrate_cameras --bag Kalib_data_vga.bag --topics /zed2/zed_node/left/image_rect_color2 /zed2/zed_node/right/image_rect_color2 --models pinhole-radtan pinhole-radtan --target april.yaml
```

1
