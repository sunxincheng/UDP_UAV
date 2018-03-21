cmake_minimum_required(VERSION 2.6)
project(udp)
add_executable(udp test.cpp UdpServer.cpp)

install(TARGETS udp RUNTIME DESTINATION bin)
