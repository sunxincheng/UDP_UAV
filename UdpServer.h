#ifndef UDPSERVER_H 
#define UDPSERVER_H

#include <iostream>
#include <stdio.h>
#include <errno.h>  
#include <sys/types.h>
#include <sys/wait.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>  
#include <netdb.h>  
#include <opencv2/opencv.hpp>
#include "System.h"
#include "FrameDrawer.h"
#include "MapDrawer.h"
#include "Tracking.h"
namespace ORB_SLAM2
{
#define SERVER_PORT 8888
#define BUFF_LEN    1024
  class System;
  class Tracking;
  class UdpServer
  {
  public:
    UdpServer(System* pSystem,Tracking* pTracker);
    void handle_udp_msg(double x,double y,double z);
    void close_server();
    void Run();
  private:
    System* mpSystem;
    Tracking* mpTracker;
    //FrameDrawer* mpFrameDrawer;
    //MapDrawer* mpMapDrawer;
    char buf[BUFF_LEN];
    socklen_t len;
    struct sockaddr_in clent_addr;
    //struct sockaddr_in ser_addr;
    struct sockaddr_in ser_addr;
    int server_fd;
  };
}
#endif