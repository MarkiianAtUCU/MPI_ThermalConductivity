cmake_minimum_required(VERSION 3.15)
project(MPI)

set(CMAKE_CXX_STANDARD 14)

add_executable(MPI src/main.cpp src/MpiTable.cpp includes/config_reader.h includes/heatmap_creator.h)
include_directories(MPI includes)