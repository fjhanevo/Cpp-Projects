cmake_minimum_required (VERSION 3.19.2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(space_game)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# ---- Shaders ----
file(GLOB SHADERS "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.glsl")

add_custom_target(copy_shaders ALL 
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/shaders
            ${CMAKE_CURRENT_BINARY_DIR}/shaders
    DEPENDS ${SHADERS}
)

# ---- Executables ----
add_executable(space_game 
    src/main.cpp 
    src/glad.c
    src/shader.cpp
    src/stb_image.cpp
)

target_include_directories(space_game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(space_game PRIVATE OpenGL::GL glfw)


add_dependencies(space_game copy_shaders)
