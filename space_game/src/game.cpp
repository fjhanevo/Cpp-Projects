#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "game.h"

void Game::play_game()
{

    // initalize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << '\n';
        return;
    }

    // set OpenGL version hints (version 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // create a window
    GLFWwindow *window = glfwCreateWindow(800, 600, "Space Game", NULL, NULL);

    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);

    // intialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << '\n';
        return;
    }

    // render loop
    while (!glfwWindowShouldClose(window)) {
        // input ...

        // rendering
        glClearColor(0.0f,0.0f,0.2f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT);

        // swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // cleanup
    glfwTerminate();
}
