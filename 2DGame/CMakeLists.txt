cmake_minimum_required(VERSION 3.10)

# set the project name
project(2DGame)

# find sfml
find_package(SFML 2.5.1 COMPONENTS graphics audio window system REQUIRED)

# add the executable
include_directories(${PROJECT_SOURCE_DIR})
add_executable(2DGame main.cpp MyClass.cpp)

# link sfml
target_link_libraries(2DGame sfml-graphics sfml-audio sfml-window sfml-system)