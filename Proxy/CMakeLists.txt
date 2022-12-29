cmake_minimum_required(VERSION 3.24)
project(Proxy)

SET(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 17)

add_executable(Proxy main.cpp Print.cpp Print.h ThreadPool.h Server.cpp Server.h ServerConfig.h ServerConfig.cpp HttpCommunication.cpp HttpCommunication.h ProxyServer.cpp ProxyServer.h)
