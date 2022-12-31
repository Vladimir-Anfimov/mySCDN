cmake_minimum_required(VERSION 3.24)
project(Supervisor)

set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(Supervisor main.cpp)

find_package(TinyHelp REQUIRED)
include_directories(${LIBHELP_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${TINYHELP_LIBRARY})