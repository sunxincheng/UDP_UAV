-------------------------------------------------------------------------------------
                                   源程序的编译方式（默认该系统已经配置好ROS环境，OpenCV，MYNTEYE等环境）
递归创建一个文件夹。
mkdir -p ROS_VIN/src

将源程序拷贝到src文件夹目录下
cp MYNT-EYE-VINS-Sample MYNT-EYE-ROS-Wrapper ~/ROS_VIN/src

cd 到ROS_VIN目录下
cd ~/ROS_VIN

采用ROS下catkin_make 进行编译
catkin_make -j2   //-jn 是指定编译的核心数，一般双核四线程，n最大为4，由于电脑棒本身性能的问题，采用，四线程容易卡死，所以我们采用n=2

编译完成时，在当前终端或新打开一个终端启动ROS系统
roscore

再新打开一个终端，启动执行相机数据的采集
cd ~/ROS_VIN
source ./devel/setup.bash //将当前的编译好程序的环境添加到ROS环境下
roslaunch mynteye_ros_wrapper mynt_camera.launch  //启动执行相机数据的采集

再新打开一个终端，启动ROS的图像显示界面】
cd ~/ROS_VIN
source ./devel/setup.bash //将当前的编译好程序的环境添加到ROS环境下
roslaunch vins_estimator vins_rviz.launch

再新打开一个终端，执行程序进行无人机的位置估计
cd ~/ROS_VIN
source ./devel/setup.bash //将当前的编译好程序的环境添加到ROS环境下
roslaunch vins_estimator mynteye.launch

----------------------------------------------------------------------------------
                       UDP数据发送与采集
进行udp数据的发送和采集需要首先修改源程序里的IP地址进行重新编译
cd ~/ROS_VINS/src/MYNT-EYE-VINS-Sample/vins_estimator/src
gedit UdpServer.cc
将ser_addr.sin_addr.s_addr = inet_addr("IP");注释去掉IP改成你需要发送的IP地址，再将
ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);添加注释，保存后重新编译MYNT-EYE-VINS-Sample。

---------------------------------------------------------------------------------
                        相机采集到的数据保存
cd 到 .ros目录下创建一个目录
cd ~/.ros
mkdir cam0  //用于保存采集到图片信息 notice：每次执行程序前注意是否存在cam0文件夹，不存在需创建一个，存在将该目录下的图片清空

数据采集完成后将采集好的IMU数据以及图片信息copy出来。
cd ~/.ros
mv cam0 ~/  //移动到主目录下
mv imu.csv imu0.csv ~/    //notice: imu.csv 是相机采集过程中的IMU数据， imu0.csv是vins_estimator程序执行过程中实际运行IMU的数据。

-------------------------------------------------------------------------------------
                 notice :   
        MYNT-EYE-ROS-Wrapper/launch目录下的mynt_camera.launch是指定相机采集的数据
                             
        MYNT-EYE-VINS-Sample/config/mynteye 目录下的mynteye_config.yaml是标定好的相机以及IMU的内参以及外参，以及程序执行的相关参数
