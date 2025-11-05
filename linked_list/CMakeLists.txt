cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

project(linked_list)

add_executable(linked_list
    src/main.cpp
    src/node.cpp
)

target_include_directories(linked_list PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include)
