cmake_minimum_required(VERSION 3.27)
project(radix)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(radix main.cpp)
