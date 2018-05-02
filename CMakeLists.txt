# CMake entry point
cmake_minimum_required (VERSION 3.0)
#set (CMAKE_CXX_STANDARD 11)

project (RayTracing)

#设置项目的头文件包含目录
include_directories(${CMAKE_SOURCE_DIR}/includes)

message(STATUS "CURRENT_HEADERS in ${CMAKE_SOURCE_DIR}")

# Compile external dependencies

set(CHAPTERS
    1.Start
    2.Vec
    3.Ray
    4.Sphere
    5.Normals
    6.MultipleObjects
    7.Antialiasing
    8.Diffuse
)

foreach(CHAPTER ${CHAPTERS})
    if (IS_DIRECTORY ${PROJECT_SOURCE_DIR}/src/${CHAPTER})               # 当前路径是一个目录吗，是的话就加入到包含目录
        message("include dir: " ${PROJECT_SOURCE_DIR}/src/${CHAPTER})
        add_subdirectory(${PROJECT_SOURCE_DIR}/src/${CHAPTER})
    endif()
endforeach(CHAPTER)


