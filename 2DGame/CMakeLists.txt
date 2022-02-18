cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Ofast")
set(CMAKE_C_FLAGS "-Ofast")

# set the project name
project(2DGame)

set(IMGUI_DIR ../libs/imgui-1.86)
set(IMGUI ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp)

set(IMGUI_SFML_DIR ../libs/imgui-sfml-2.5)
set(IMGUI_SFML ${IMGUI_SFML_DIR}/imgui-SFML.cpp)

set(RAPIDXML_DIR ../libs/rapidxml-1.13/)
set(RAPIDXML ${RAPIDXML_DIR}/rapidxml.hpp ${RAPIDXML_DIR}/rapidxml_utils.hpp ${RAPIDXML_DIR}/rapidxml_print.hpp ${RAPIDXML_DIR}/rapidxml_iterators.hpp)

# Note: We do not recommend using GLOB to collect a list of source files from your source tree. 
# If no CMakeLists.txt file changes when a source is added or removed then the generated build 
# system cannot know when to ask CMake to regenerate. The CONFIGURE_DEPENDS flag may not work 
# reliably on all generators, or if a new generator is added in the future that cannot support 
# it, projects using it will be stuck. Even if CONFIGURE_DEPENDS works reliably, there is still
# a cost to perform the check on every rebuild.
file(GLOB_RECURSE 2DGame_SRC
     "*.h"
     "*.cpp"
)

# add the executable
include_directories(${PROJECT_SOURCE_DIR})
add_executable(2DGame ${2DGame_SRC} ${IMGUI} ${IMGUI_SFML} ${RAPIDXML})

target_include_directories(2DGame PRIVATE ${IMGUI_DIR})
target_include_directories(2DGame PRIVATE ${IMGUI_SFML_DIR})
target_include_directories(2DGame PRIVATE ${RAPIDXML_DIR})

# find and link sfml and opengl
find_package(SFML 2.5.1 COMPONENTS graphics audio window system REQUIRED)
set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(OpenGL REQUIRED)
target_link_libraries(2DGame sfml-graphics sfml-audio sfml-window sfml-system ${OPENGL_gl_LIBRARY})

file(COPY data DESTINATION ${CMAKE_BINARY_DIR})