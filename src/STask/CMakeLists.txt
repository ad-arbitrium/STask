cmake_minimum_required(VERSION 3.5)

project(STask)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

add_library(stask SHARED IOManager.cpp Logger.cpp SisyphusUtils.h UserManager.cpp)
