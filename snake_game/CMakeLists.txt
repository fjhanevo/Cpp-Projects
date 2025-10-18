cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

project(snake_game)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)


configure_file(config.h.in config.h)
include_directories(${FREETYPE_INCLUDE_DIRS})

# ---- Executables ---- 
add_executable(snake_game
    src/main.cpp
    src/game.cpp
    src/snake.cpp
    src/food.cpp
    src/border.cpp
    src/extern/glad.c
    src/extern/shader.cpp
    src/extern/texture.cpp
    src/extern/resource_manager.cpp
    src/extern/sprite_renderer.cpp
    src/extern/text_renderer.cpp
    src/extern/stb_image.cpp

)


target_include_directories(snake_game PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include         # for header files
    ${CMAKE_CURRENT_SOURCE_DIR}/libs            # for external headers
    ${CMAKE_BINARY_DIR}
)
target_link_libraries(snake_game PRIVATE OpenGL::GL glfw)
target_link_libraries(snake_game PRIVATE ${FREETYPE_LIBRARIES})


