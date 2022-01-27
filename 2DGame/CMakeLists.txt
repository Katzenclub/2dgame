cmake_minimum_required(VERSION 3.10)

# set the project name
project(2DGame)

# find sfml
find_package(SFML 2.5.1 COMPONENTS graphics audio window system REQUIRED)

#Note: We do not recommend using GLOB to collect a list of source files from your source tree. 
#If no CMakeLists.txt file changes when a source is added or removed then the generated build 
#system cannot know when to ask CMake to regenerate. The CONFIGURE_DEPENDS flag may not work 
#reliably on all generators, or if a new generator is added in the future that cannot support 
#it, projects using it will be stuck. Even if CONFIGURE_DEPENDS works reliably, there is still
#a cost to perform the check on every rebuild.
file(GLOB_RECURSE 2DGame_SRC
     "*.h"
     "*.cpp"
)

# add the executable
include_directories(${PROJECT_SOURCE_DIR})
add_executable(2DGame ${2DGame_SRC})

# link sfml
target_link_libraries(2DGame sfml-graphics sfml-audio sfml-window sfml-system)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})