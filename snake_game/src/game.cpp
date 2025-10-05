#include "game.h"
#include "shader.h"
#include "texture.h"
#include "sprite_renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "config.h"
#include "snake.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

SpriteRenderer *Renderer;
std::string vert_path = std::string(RESOURCE_DIR) + "/shaders/sprite.vert";
std::string frag_path = std::string(RESOURCE_DIR) + "/shaders/sprite.frag";


Game::Game(unsigned int width, unsigned int height)
: screen_width(width), screen_height(height), window(nullptr), state(GAME_ACTIVE), snake(width, height)
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

    // Create a texture placeholder
    unsigned char white_px[3] = { 255, 255, 255 };
    Texture2D temp_tex;
    temp_tex.generate(1, 1, white_px);
    ResourceManager::textures["temp"] = temp_tex;


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
    glClearColor(0.3f, 0.5f, 0.0f, 1.0f);   // draw a green background
    glClear(GL_COLOR_BUFFER_BIT);
    draw_borders();
    snake.draw(*Renderer);

    glfwSwapBuffers(window);
}

void Game::cleanup()
{
    delete Renderer;
    ResourceManager::clear();
    glfwTerminate();
}

// ----- Game functions ----- 
void Game::draw_borders()
{
    Texture2D border_tex = ResourceManager::get_texture("temp");
    glm::vec3 border_color = glm::vec3(0.6f, 0.3f, 0.0f);
    float tile_size = 20.0f;
    // draw top and bottom border
    for (unsigned int x = 0; x < this->screen_width; x++)
    {
        // top border
        Renderer->draw_sprite(
            border_tex,
            glm::vec2(x, 0.0f),
            glm::vec2(tile_size, tile_size),
            0.0f, border_color
        );
        // Bottom border
        Renderer->draw_sprite(
            border_tex,
            glm::vec2(x, this->screen_height - tile_size),
            glm::vec2(tile_size, tile_size),
            0.0f, border_color
        );
    }

    for (unsigned int y = 0; y < this->screen_height; y++)
    {
        // Right column
        Renderer->draw_sprite(
            border_tex,
            glm::vec2(0.0f, y),
            glm::vec2(tile_size, tile_size),
            0.0f, border_color
        );

        // Left column
        Renderer->draw_sprite(
            border_tex,
            glm::vec2(this->screen_width - tile_size, y),
            glm::vec2(tile_size, tile_size),
            0.0f, border_color
        );
    }
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
}


