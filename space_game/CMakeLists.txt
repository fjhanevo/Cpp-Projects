cmake_minimum_required (VERSION 3.19.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(space_game)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(space_game src/main.cpp src/glad.c)

target_include_directories(space_game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(space_game PRIVATE OpenGL::GL glfw)
