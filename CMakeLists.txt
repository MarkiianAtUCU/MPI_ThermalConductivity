cmake_minimum_required(VERSION 3.15)
project(Mpi_Thermal)

set(CMAKE_CXX_STANDARD 14)

find_package(MPI REQUIRED)
set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
include_directories(MPI_INCLUDE_PATH)

add_executable(Mpi_Thermal src/main.cpp src/MpiTable.cpp src/MpiManager.cpp)
#target_link_libraries(Mpi_Thermal, ${MPI_LIBRARIES})
include_directories(Mpi_Thermal includes)