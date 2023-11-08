cmake_minimum_required(VERSION 3.5)

project(STask)

set(SOURCE_DIR src/STask)
set(HEADER_DIRS src/STask)

add_compile_options(
    -std=c++20
)

add_library(STask0 STATIC 
    ./src/STask/IOManager.cpp
    ./src/STask/STask.cpp
    ./src/STask/UserManager.cpp
)

