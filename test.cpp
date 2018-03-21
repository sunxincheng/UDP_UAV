#include "UdpServer.hpp"

int main()
{
  UdpServer udpserver;
  double x,y,z;
  x=1.0;
  y=2.0;
  z=3.0;
  while(1)
  {
    //x+=1.0;
    udpserver.handle_udp_msg(x,y,z);
  }
  udpserver.close_server();
  return 0;
}