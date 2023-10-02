# i doubt this works
cmake_minimum_required(VERSION 3.0)
project(STask VERSION 0.0.1 DESCRIPTION "Simple Task-tracking service" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE sources *.cpp *.h)
file(GLOB_RECURSE test test/*.cpp test/*.h)

add_library(stask-lib sources)

add_executable(stask-test test)