cmake_minimum_required(VERSION 3.26)
project(let6_DB)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(let6_DB
        let6.cpp
        let6.h)
