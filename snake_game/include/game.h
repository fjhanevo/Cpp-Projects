#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game {
public:
    Game(unsigned int width, unsigned int height);
    ~Game();

    void run();
private:
    GLFWwindow *window;
    unsigned int screen_width, screen_height;
    GameState state;
    void init();
    void cleanup();
    void render();
    void process_input();
    
    // callback wrappers
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
};
