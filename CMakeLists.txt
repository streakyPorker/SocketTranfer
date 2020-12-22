cmake_minimum_required(VERSION 3.17)
project(cnlab7 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
add_executable(cnlab7 server.c)