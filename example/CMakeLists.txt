cmake_minimum_required(VERSION 3.0.0)
project(RwCBufExample VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

add_executable(RwCBufExample RwCBufExample.cpp)

install(TARGETS RwCBufExample DESTINATION bin)

