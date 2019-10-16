cmake_minimum_required(VERSION 3.15)
project(MPI)

set(CMAKE_CXX_STANDARD 14)

add_executable(MPI src/main.cpp includes/config_reader.h includes/MpiTable.h src/MpiTable.cpp)