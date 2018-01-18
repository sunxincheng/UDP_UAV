#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>  
#include <netdb.h>  
#include <string.h>
#include <unistd.h>

#define SERVER_PORT 8888
#define BUFF_LEN 1024
#define SERVER_IP "172.26.24.64"

class UdpClient
{
public:
  UdpClient();
  void udp_msg_sender();
  void close_client();
private:
  int client_fd;
  socklen_t len;
  struct sockaddr_in ser_addr;
  struct sockaddr_in src;
  char buf[BUFF_LEN];
};

