#include "game.h"
#include "shader.h"
#include "sprite_renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include <GLFW/glfw3.h>
#include "config.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer *Renderer;
std::string vert_path = std::string(RESOURCE_DIR) + "/shaders/sprite.vert";
std::string frag_path = std::string(RESOURCE_DIR) + "/shaders/sprite.frag";
std::string texture_path = std::string(RESOURCE_DIR) + "/textures/sofie.png";

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

    // load shaders
    ResourceManager::load_shader(vert_path.c_str(), frag_path.c_str(), "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->screen_width),
                           static_cast<float>(this->screen_height), 0.0f, -1.0f, 1.0f);
    ResourceManager::get_shader("sprite").use().set_int("image", 0);
    ResourceManager::get_shader("sprite").set_mat4("projection", projection);

    Shader shader = ResourceManager::get_shader("sprite");
    Renderer = new SpriteRenderer(shader);
    ResourceManager::load_texture(texture_path.c_str(), true, "sofie");

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    Texture2D tex = ResourceManager::get_texture("sofie");
    Renderer->draw_sprite(tex,
        glm::vec2(200.f, 200.f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    glfwSwapBuffers(window);
}

void Game::cleanup()
{
    delete Renderer;
    ResourceManager::clear();
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


