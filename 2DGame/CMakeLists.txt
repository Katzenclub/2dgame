cmake_minimum_required(VERSION 3.10)

# set the project name
project(2DGame)

# add the executable
include_directories(${PROJECT_SOURCE_DIR})
add_executable(2DGame main.cpp MyClass.cpp)