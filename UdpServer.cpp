#include "UdpServer.hpp"


UdpServer::UdpServer()
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
