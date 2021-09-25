cmake_minimum_required(VERSION 3.20)
get_filename_component(project_dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${project_dir_name})

set(CMAKE_CXX_STANDARD 17)

file(GLOB cpps ${PROJECT_SOURCE_DIR}/sources/*.cpp)
file(GLOB hpps ${PROJECT_SOURCE_DIR}/sources/*.hpp)

#Boost
set(Boost_USE_STATIC_LIBS ON)
message("Try to find boost")
find_package(Boost)
if(NOT BOOST_FOUND)
    message("Set boost root")
    set(Boost_ROOT C:/Libraries/boost)

    message("Try to find boost")
    find_package(Boost REQUIRED)
endif()

if(Boost_FOUND)
    message(${Boost_INCLUDE_DIR})
    include_directories(${Boost_INCLUDE_DIR})

    message(${Boost_LIBRARY_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()

add_executable(${PROJECT_NAME} ${hpps} ${cpps})

if(Boost_FOUND)
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()