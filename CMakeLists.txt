cmake_minimum_required(VERSION 3.24)
project(Rubix_cube_project_clion)

set(CMAKE_CXX_STANDARD 20)

add_executable(Rubix_cube_project_clion main.cpp GenericRubiksCube.cpp GenericRubiksCube.h++ RubiksCube3DArray.cpp RubiksCube1DArray.cpp)
