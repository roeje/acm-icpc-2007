cmake_minimum_required(VERSION 3.3)
project(icpc2007)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES icpc2007.cpp)
add_executable(icpc2007 ${SOURCE_FILES} icpc2007.cpp)