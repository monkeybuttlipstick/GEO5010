cmake_minimum_required(VERSION 3.20)
project(tiling_mesh)
set(CMAKE_CXX_STANDARD 14)
set(BOOST_ROOT "C:/dev/boost")
find_package(CGAL REQUIRED)


add_executable(tiling_mesh main.cpp)

find_package(Eigen3 3.1.0 QUIET) #(3.1.0 or greater)
include(CGAL_Eigen3_support)


