#include "UdpClient.hpp"
/*
 * client:
 *        socket---->sendto---->revcform---->close
*/
UdpClient::UdpClient()
{
  client_fd = socket(AF_INET, SOCK_DGRAM, 0);
   if(client_fd < 0)
  {
    std::cout<<"create socket fail!"<<std::endl;
    return ;
  }
  memset(&ser_addr, 0, sizeof(ser_addr));
  ser_addr.sin_family = AF_INET;
  ser_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  //ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ser_addr.sin_port        = htons(SERVER_PORT);
  std::cout<<"client:TEST UDP MSG!"<<std::endl;
}

void UdpClient::udp_msg_sender()
{
    len = sizeof(ser_addr);
    sendto(client_fd, buf, BUFF_LEN, 0, (struct sockaddr*)&ser_addr, len);
    memset(buf,0,BUFF_LEN);
    recvfrom(client_fd,buf, BUFF_LEN, 0, (struct sockaddr*)&src, &len);
    std::cout<<"server: "<<buf<<std::endl;
    //sleep(0.2);
}

void UdpClient::close_client()
{
  close(client_fd);
}
