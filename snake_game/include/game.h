#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "snake.h"
#include "food.h"

enum GameState {
    GAME_ACTIVE,
    GAME_PAUSE,
    GAME_LOST
};

class Game {
public:
    Game(unsigned int width, unsigned int height);
    ~Game();

    void run();
private:
    unsigned int screen_width, screen_height;
    unsigned int score;
    GLFWwindow *window;
    GameState state;
    Snake *snake;
    Food *food;
    bool keys[1024];
    bool keys_processed[1024];

    void init();
    void init_snake();
    void update(float dt);
    void render();
    void process_input();
    void cleanup();
    void play_again();

    // ----- Snake specific functions ----- 
    void draw_borders();
    void spawn_food();
    void check_collision();
    float move_timer = 0.0f; 

    // callback wrappers
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};
