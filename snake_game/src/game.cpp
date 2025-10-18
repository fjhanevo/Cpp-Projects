#include "game.h"
#include "shader.h"
#include "snake.h"
#include "texture.h"
#include "sprite_renderer.h"
#include "texture.h"
#include "resource_manager.h"
#include "config.h"
#include "text_renderer.h"

#include <random>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <sstream>
#include <glm/gtc/matrix_transform.hpp>


std::mt19937 dev;
std::random_device r;
std::uniform_int_distribution<> dist_x(1, SCREEN_WIDTH  / TILE_SIZE - 2);
std::uniform_int_distribution<> dist_y(1, SCREEN_HEIGHT / TILE_SIZE - 2);


SpriteRenderer *Renderer;
TextRenderer *Text;
std::string vert_path = std::string(RESOURCE_DIR) + "/shaders/sprite.vert";
std::string frag_path = std::string(RESOURCE_DIR) + "/shaders/sprite.frag";
std::string font_path = std::string(RESOURCE_DIR) + "/fonts/slkscr.ttf";


Game::Game(unsigned int width, unsigned int height) :
    screen_width(width), screen_height(height), score(0), window(nullptr), 
    state(GAME_ACTIVE),snake(nullptr), food(nullptr), border(nullptr),
    keys(), keys_processed()
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
    Text = new TextRenderer(this->screen_width, this->screen_height);
    Text->load(font_path.c_str(), 24);

    // Create a texture placeholder
    unsigned char white_px[3] = { 255, 255, 255 };
    Texture2D temp_tex;
    temp_tex.generate(1, 1, white_px);
    ResourceManager::textures["temp"] = temp_tex;

    // Create Snake and Food objects
    this->snake = new Snake(this->screen_width, this->screen_height);
    this->food = new Food();
    this->border = new Border(this->screen_width, this->screen_height);
    // assign border texture
}

void Game::run()
{
    float delta_time = 0.0f;
    float last_frame = 0.0f;

    while(!glfwWindowShouldClose(window)) {
        float current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        process_input();
        update(delta_time);
        render();
    }
}

void Game::update(float dt)
{
    const float MOVE_INTERVAL = 0.15f;  // the snake will move every 0.15 seconds
    if (this->state == GAME_ACTIVE)
    {
        this->move_timer += dt;

        // check if enough time has passed to move the snake
        if (this->move_timer >= MOVE_INTERVAL)
        {
            Direction next_dir = this->snake->get_next_direction();
            this->snake->set_direction(next_dir);
            this->snake->move();
            this->move_timer = 0.0f;
        }
        
        this->food->update(dt);
        check_collision();

        if (!this->food->is_active)
            spawn_food();
    }
}

void Game::process_input()
{
    if (this->keys[GLFW_KEY_P] && !this->keys_processed[GLFW_KEY_P])
    {
        if (this->state == GAME_ACTIVE)
            this->state = GAME_PAUSE;
        else if (this->state == GAME_PAUSE)
            this->state = GAME_ACTIVE;
        this->keys_processed[GLFW_KEY_P] = true;
    }
    
    if (this->state == GAME_ACTIVE) 
    {
        Direction new_dir = this->snake->get_next_direction();
        if (this->keys[GLFW_KEY_W]) new_dir = Direction::UP;
        if (this->keys[GLFW_KEY_A]) new_dir = Direction::LEFT;
        if (this->keys[GLFW_KEY_S]) new_dir = Direction::DOWN;
        if (this->keys[GLFW_KEY_D]) new_dir = Direction::RIGHT;

        Direction current_dir = this->snake->get_current_direction();
        // prevent reversing the direction
        if (!((current_dir == Direction::UP && new_dir == Direction::DOWN) ||
             (current_dir == Direction::DOWN && new_dir == Direction::UP) ||
             (current_dir == Direction::LEFT && new_dir == Direction::RIGHT) ||
             (current_dir == Direction::RIGHT && new_dir == Direction::LEFT)))
        {
            this->snake->queue_direction(new_dir);
        } 
    }
    if (this->state == GAME_LOST)
    {
        if (this->keys[GLFW_KEY_Y] && !this->keys_processed[GLFW_KEY_Y]) 
        {
            this->play_again();
            this->keys_processed[GLFW_KEY_Y] = true;
        }
        if (this->keys[GLFW_KEY_N] && !this->keys_processed[GLFW_KEY_N]) 
        {
            glfwSetWindowShouldClose(this->window, true);
            this->keys_processed[GLFW_KEY_N] = true;
        }
    }

    glfwPollEvents();
}

void Game::render()
{
    if (this->state == GAME_ACTIVE)
    {
        glClearColor(0.3f, 0.5f, 0.0f, 1.0f);   // draw a green background
        glClear(GL_COLOR_BUFFER_BIT);
        this->border->draw(*Renderer);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        this->snake->draw(*Renderer);
        this->food->draw(*Renderer);
        std::stringstream ss; ss << this->score;
        Text->render_text("Score:"+ss.str(), TILE_SIZE, TILE_SIZE, 1.0f);

    }

    if (this->state == GAME_LOST)
    {
        std::stringstream ss; ss << this->score;
        Text->render_text(
            "Your Score:"+ss.str(), 
            floor(SCREEN_WIDTH / (2.0f * TILE_SIZE)) * TILE_SIZE,
            floor(SCREEN_HEIGHT / (2.0f * TILE_SIZE)) * TILE_SIZE,
            1.0
        );
        
        Text->render_text(
            "Play Again [y/N]",
            floor(SCREEN_WIDTH / (2.0f * TILE_SIZE)) * TILE_SIZE,
            floor(SCREEN_HEIGHT / (2.0f * TILE_SIZE)) * TILE_SIZE + TILE_SIZE,
            1.0
        );

    }
    glfwSwapBuffers(window);
}

void Game::cleanup()
{
    delete Renderer;
    delete Text;
    delete snake;
    delete food;
    delete border;
    ResourceManager::clear();
    glfwTerminate();
}

// ----- Game functions ----- 
void Game::play_again()
{
    this->snake->reset_snake(this->screen_width, this->screen_height);
    this->score = 0;
    if (this->food->is_active)
        this->food->is_active = false;
    this->state = GAME_ACTIVE;
}

void Game::spawn_food()
{
    bool is_valid = false;
    glm::vec2 pos;
    while (!is_valid) 
    {
        pos.x = dist_x(r) * TILE_SIZE;
        pos.y = dist_y(r) * TILE_SIZE;

        // assume position is valid, check it doesn't spawn on the snake
        is_valid = true;
        
        for (const auto& segment : this->snake->get_segments())
        {
            if (segment.x == pos.x && segment.y == pos.y)
            {
                is_valid = false;
                break;
            }
        }
    }
    this->food->spawn(pos);
}

void Game::check_collision()
{
    // check snake_head and food collision
    if (this->food->is_active)
    {
        if (this->snake->get_head_position() == this->food->position)
        {
            this->snake->grow();
            this->food->is_active = false;

            this->score++;  
        }
    }

    // check border collision
    glm::vec2 snake_head_pos = this->snake->get_head_position();
    if (snake_head_pos.x < TILE_SIZE ||
        snake_head_pos.x >= SCREEN_WIDTH - TILE_SIZE||
        snake_head_pos.y < TILE_SIZE ||
        snake_head_pos.y >= SCREEN_HEIGHT - TILE_SIZE
    ) this->state = GAME_LOST;
    
    // check self collision
    std::vector<glm::vec2> segments = this->snake->get_segments(); 
    
    // can't crash with itself if the length of the snake is less than 4
    if (segments.size() < 4)
        return;

    for (size_t i = 1; i < segments.size(); i++)
    {
        if (snake_head_pos  == segments[i]) 
        {
            this->state = GAME_LOST;
            break;
        }
    }
}

// ----- Static callback functions -----
void Game::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // get the game instance
    Game *game = static_cast<Game*>(glfwGetWindowUserPointer(window));
    if (game) 
    {
        if (key == GLFW_KEY_Q && action == GLFW_PRESS ||
            key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (key >= 0 && key < 1024)
        {
            if (action == GLFW_PRESS)
                game->keys[key] = true;
            else if (action == GLFW_RELEASE)
            {
                game->keys[key] = false;
                game->keys_processed[key] = false;
            }
                
        }
    }
}

void Game::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}


