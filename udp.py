import time
import socket

HOST='192.168.2.4'
PORT=8008
BUFFER=4096

while 1:
soc=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    
    soc.connect((HOST,PORT))
    
    time.sleep(1)
    
    soc.send('hello ros')
    
    buf=soc.recv(BUFFER)
    打印消息
    print(buf)
    
    soc.close()
