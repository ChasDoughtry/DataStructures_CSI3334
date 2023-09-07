cmake_minimum_required(VERSION 3.23)
project(Project_3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-static")

add_executable(Project_3 driver-proj3.cpp bst-prof-proj3.h bst-student-proj3.h)
