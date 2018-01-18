#include "UdpClient.hpp"

int main()
{
  UdpClient udpclient;
  int i=0;
  while(1)
  {
    std::cout<<i++<<std::endl;
    udpclient.udp_msg_sender();
  }
  
  udpclient.close_client();
}
