cmake_minimum_required(VERSION 3.24)
project(Proxy)

set(CMAKE_CXX_STANDARD 17)

add_executable(Proxy main.cpp Print.cpp Print.h ThreadPool.cpp ThreadPool.h)
