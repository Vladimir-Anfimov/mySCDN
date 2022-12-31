cmake_minimum_required(VERSION 3.24)
project(LibHelp)

set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        Print.cpp
        Print.h
        ThreadPool.h
        Server.cpp
        Server.h
        ServerConfig.h
        ServerConfig.cpp
        HttpCommunication.cpp
        HttpCommunication.h
        TcpCommunication.h
        TcpCommunication.cpp
        Client.h
        Client.cpp
        StandardCommunication.h)

add_library(LibHelp ${SOURCE_FILES})
#add_executable(LibHelp ${SOURCE_FILES})