cmake_minimum_required(VERSION 3.13)
project(engine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(external/LiteMath)

add_executable(engine 
               main.cpp
               bitmap.cpp
               external/LiteMath/Image2d.cpp
)