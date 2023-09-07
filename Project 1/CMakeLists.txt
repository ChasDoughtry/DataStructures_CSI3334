cmake_minimum_required(VERSION 3.23)
project(Project_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-static")
add_executable(Project_1 driver-proj1.cpp stack-proj1.cpp maze-proj1.cpp location-proj1.cpp location-proj1.h maze-proj1.h stack-proj1.h oldTestDrivers.cpp)
