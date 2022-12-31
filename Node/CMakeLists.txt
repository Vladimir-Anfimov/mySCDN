cmake_minimum_required(VERSION 3.24)
project(Node)

set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(
        Node
        main.cpp
        DataLayer/DatabaseContext.cpp
        Infrastructure/TcpServer.h
        Infrastructure/TcpServer.cpp
        DataLayer/CacheRepository.h
        DTO/CacheDto.h
        Common/Mapper.h
        BusinessLayer/CacheService.cpp
        Common/Command.h
        DTO/CacheUpsertDto.h)

find_package(TinyHelp REQUIRED)
include_directories(${LIBHELP_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${TINYHELP_LIBRARY} sqlite3)