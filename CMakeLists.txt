cmake_minimum_required(VERSION 3.20)
get_filename_component(project_dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${project_dir_name})

set(CMAKE_CXX_STANDARD 17)

file(GLOB cpps ${PROJECT_SOURCE_DIR}/sources/*.cpp)
file(GLOB hpps ${PROJECT_SOURCE_DIR}/sources/*.hpp)

add_executable(${PROJECT_NAME} ${hpps} ${cpps})