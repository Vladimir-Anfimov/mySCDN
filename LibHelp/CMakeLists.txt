cmake_minimum_required(VERSION 3.24)
project(LibHelp)

set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp
        Print.cpp
        Print.h
        ThreadPool.h
        Server.cpp
        Server.h
        ServerConfig.h
        ServerConfig.cpp
        HttpCommunication.cpp
        HttpCommunication.h)

add_library(LibHelp ${SOURCE_FILES})
