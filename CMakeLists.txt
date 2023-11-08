cmake_minimum_required(VERSION 3.5)

project(STask)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

set(SOURCE
    ./src/STask/IOManager.cpp
    ./src/STask/UserManager.cpp
    ./src/STask/Logger.cpp
)

add_library(SSTask STATIC ${SOURCE})

add_library(STask SHARED ${SOURCE})

add_executable(STaskTest ./src/STask/test/STask.cpp)

target_link_libraries(STaskTest
    SSTask    
)

