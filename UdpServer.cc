#include "UdpServer.h"
#include <System.h>
#include "opencv2/opencv.hpp"

namespace ORB_SLAM2 
{
  UdpServer::UdpServer(System* pSystem,Tracking* pTracker):mpSystem(pSystem),mpTracker(pTracker)
{
}

  
void UdpServer::handle_udp_msg(double x,double y,double z)
{
  memset(buf, 0,BUFF_LEN);
  using namespace std;
  sprintf(buf,"X=%f\nY=%f\nZ=%f\n",x,y,z); //reply the client
  sendto(server_fd,buf,BUFF_LEN,0,(struct sockaddr*)&clent_addr,len);//send the msg to client,notice using the(struct sockaddr*)
}


void UdpServer::close_server()
{
    close(server_fd);
}

void UdpServer::Run()
{
  int ret;
  server_fd = socket(AF_INET,SOCK_DGRAM,0);//AF_INET:IPV4;SOCK_DGRAM:UDP   PF_INET6:IPV6
  if(server_fd < 0)
  {
    std::cout<<"create socket fail!"<<std::endl;
    return ;
  }
  
  memset(&ser_addr, 0, sizeof(ser_addr));
  
  ser_addr.sin_family      = AF_INET;
  //IP地址，需要进行网络序转换，INADDR_ANY：本地地址
  //ser_addr.sin_addr.s_addr = inet_addr("172.26.24.64");
  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ser_addr.sin_port        = htons(SERVER_PORT);
  
  
//   ser_addr.sin6_family  =  PF_INET6;
//   ser_addr.sin6_port    =  htons(SERVER_PORT);
   ret = bind(server_fd, (struct sockaddr* )&ser_addr, sizeof(ser_addr));
  
  if(ret < 0)
  {
    std::cout<<"socket bind fail!"<<std::endl;
    return ;
  }
  memset(buf,0,BUFF_LEN);
  len = sizeof(clent_addr);
  int count;
  count = recvfrom(server_fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, &len); //recvfrom
  if(count == -1)
  {
    std::cout<<"recieve data failed!"<<std::endl;
    return;
  }
  while(1)
  {
    cv::Mat mTcw = mpTracker->mCurrentFrame.mTcw.clone();
    if(!mTcw.empty())
    {
      cv::Mat mRcw = mTcw.rowRange(0,3).colRange(0,3);
      cv::Mat mtcw = mTcw.rowRange(0,3).col(3);
      cv::Mat mOw = -mRcw.t()*mtcw;
      double x = mOw.at<float>(0,0);
      double y = mOw.at<float>(1,0);
      double z = mOw.at<float>(2,0);
      handle_udp_msg(x,y,z);
    }
    else
    {
    }
  }  
}

} //namespace ORB_SLAM2
