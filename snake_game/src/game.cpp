#include "game.h"
#include "shader.h"
#include "texture.h"
#include "resource_manager.h"
#include <GLFW/glfw3.h>
#include <iostream>



Game::Game(unsigned int width, unsigned int height)
: screen_width(width), screen_height(height), window(nullptr), state(GAME_ACTIVE)
{
    init();
}

Game::~Game()
{
    cleanup(); 
}

void Game::init()
/* Make the window */
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(this->screen_width, this->screen_height, "Snake", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW Window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    // store pointer to this Game instance in the window
    glfwSetWindowUserPointer(window, this);
    // set callback functions
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // load openGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return;
    }
    // glViewport(0, 0, this->screen_width, this->screen_height);
}

void Game::run()
{
    while(!glfwWindowShouldClose(window)) {
        process_input();
        render();
    }
}

void Game::process_input()
{
    glfwPollEvents();
}

void Game::render()
{
    glClearColor(0.2f, 0.6f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void Game::cleanup()
{
    glfwTerminate();
}


// ----- Static callback functions -----

void Game::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // get Game instance
    Game *game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    if (game) {
        if (key == GLFW_KEY_Q && action == GLFW_PRESS ||
            key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
}

void Game::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    Game *game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    if (game) {
        game->screen_width = width;
        game->screen_height = height;
    }
}


