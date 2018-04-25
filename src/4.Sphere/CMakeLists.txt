# CMake entry point
cmake_minimum_required (VERSION 3.0)
#set (CMAKE_CXX_STANDARD 11)

project (Sphere)

#在当前目录下搜索头文件及源文件
file(GLOB_RECURSE CURRENT_HEADERS  *.h *.hpp *inc)
file(GLOB CURRENT_SOURCES  *.cpp)
#为头文件和源文件进行分组
source_group("Include" FILES ${CURRENT_HEADERS})
source_group("Source" FILES ${CURRENT_SOURCES})

message(STATUS "CURRENT_HEADERS in ${CMAKE_SOURCE_DIR}")

add_executable(Sphere ${CURRENT_HEADERS} ${CURRENT_SOURCES})

