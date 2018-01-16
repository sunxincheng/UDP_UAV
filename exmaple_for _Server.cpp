#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define SERVER_PORT 8888
#define BUFF_LEN    1024

void handle_udp_msg(int fd)
{
  char buf[BUFF_LEN];
  socklen_t len;
  int count;
  struct sockaddr_in clent_addr; //IP for msg sender;
  
  while(1)
  {
    memset(buf, 0, BUFF_LEN);
    len = sizeof(clent_addr);
    count = recvfrom(fd, buf, BUFF_LEN, 0, (struct sockaddr*)&clent_addr, &len); //recvfrom 
    
    if(count == -1)
    {
      printf("recieve data failed!\n");
      return;
    }
    
    printf("client:%s\n",buf); //print the messsage
    memset(buf, 0,BUFF_LEN);
    sprintf(buf,"I have recieved %d bytes data!\n",count); //reply the client
    printf("server:%s\n",buf);//print the message you send
    /*int PASCAL FAR sendto( SOCKET s, const char FAR* buf, int len, int flags,const struct sockaddr FAR* to, int tolen);　　
         * s：一个标识套接口的描述字。　
         * buf：包含待发送数据的缓冲区。　　
         * len：buf缓冲区中数据的长度。　
         * flags：调用方式标志位。　　
         * to：（可选）指针，指向目的套接口的地址。　
         * tolen：to所指地址的长度。  
　　 */
    sendto(fd,buf,BUFF_LEN,0,(struct sockaddr*)&clent_addr,len);//send the msg to client,notice using the(struct sockaddr*)
  }
}

/*
 *     server:
 *              socket---->bind---->recvfrom---->sendto---->close 
*/

int main(int argc, char **argv)
{
  int server_fd, ret;
  struct sockaddr_in ser_addr;
  
  server_fd = socket(AF_INET,SOCK_DGRAM,0);//AF_INET:IPV4;SOCK_DGRAM:UDP
  if(server_fd < 0)
  {
    printf("create socket fail!\n");
    return -1;
  }
  
  memset(&ser_addr, 0, sizeof(ser_addr));
  ser_addr.sin_family      = AF_INET;
  
  ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  ser_addr.sin_port        = htons(SERVER_PORT);
  
  ret = bind(server_fd, (struct sockaddr* )&ser_addr, sizeof(ser_addr));
  if(ret < 0)
  {
    printf("socket bind fail!\n");
    return -1;
  }
  
  handle_udp_msg(server_fd); //solve the recieved msg 
  close(server_fd);
  return 0;
}
