cmake_minimum_required(VERSION 3.23)
project(Project_2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-static")

add_executable(Project_2 driver-proj2.cpp location-proj2.h maze-proj2.h arrayqueue-prof-proj2.h arrayqueue-student-proj2.h location-proj2.cpp maze-proj2.cpp)
