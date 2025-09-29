cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(snake_game)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# ---- Executables ---- 
add_executable(snake_game
    src/main.cpp
    src/glad.c
)


target_include_directories(snake_game PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include         # for header files
    ${CMAKE_CURRENT_SOURCE_DIR}/libs            # for external headers
)
target_link_libraries(snake_game PRIVATE OpenGL::GL glfw)


