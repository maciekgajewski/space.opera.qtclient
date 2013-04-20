cmake_minimum_required(VERSION 2.8.8)

project(clinet)

SET(CMAKE_CXX_FLAGS "-std=c++11")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Network REQUIRED)
find_package(Qt5Declarative REQUIRED)
find_package(Qt5Core REQUIRED)



add_subdirectory(client)
add_subdirectory(protocol_cpp)
add_subdirectory(textclient)
add_subdirectory(uiclient)

