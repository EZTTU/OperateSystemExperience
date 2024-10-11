cmake_minimum_required(VERSION 3.28)
project(OperateSystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(OperateSystem main.cpp)
add_executable(SevenSegment parctice/SevenSegment.cpp)
add_executable(StateMachine parctice/StateMachine.c)
add_executable(MemoryShareVerify parctice/MemoryShareVerify.cpp)