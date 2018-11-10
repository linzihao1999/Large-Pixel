cmake_minimum_required(VERSION 3.9)
project(temp)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-g -Wall")
add_executable(temp Main.cpp Screen.cpp Screen.cpp Screen.h ConstNum.h)

target_link_libraries(temp ${GLUT_LIBRARY} ${OPENGL_LIBRARY})