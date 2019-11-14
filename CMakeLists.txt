cmake_minimum_required(VERSION 3.15)
project(LZWDecoder)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O3")

add_executable(LZWDecoder main.cpp LZWEncoder/lzw_tree_encoder.cpp)