cmake_minimum_required(VERSION 3.7)
project(codejam)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES horse/horses.cpp)
add_executable(codejam ${SOURCE_FILES})
add_executable(horses horse/horses.cpp)
add_executable(leader leader/leader.cpp)