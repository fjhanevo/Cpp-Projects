cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(snake_game)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

configure_file(config.h.in config.h)

# ---- Executables ---- 
add_executable(snake_game
    src/main.cpp
    src/game.cpp
    src/extern/glad.c
    src/extern/shader.cpp
    src/extern/stb_image.cpp
)


target_include_directories(snake_game PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include         # for header files
    ${CMAKE_CURRENT_SOURCE_DIR}/libs            # for external headers
)
target_link_libraries(snake_game PRIVATE OpenGL::GL glfw)


