cmake_minimum_required(VERSION 3.24)
project(Node)

set(CMAKE_CXX_STANDARD 17)
add_executable(Node main.cpp Database.cpp Database.h)

target_link_libraries(Node LINK_PUBLIC sqlite3)
