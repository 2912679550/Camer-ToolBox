catkin init
catkin config --extend /opt/ros/noetic
catkin config --merge-devel # Necessary for catkin_tools >= 0.4.
catkin config --cmake-args -DCMAKE_BUILD_TYPE=Release

catkin build -DCMAKE_BUILD_TYPE=Release -j4