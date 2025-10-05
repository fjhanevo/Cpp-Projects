#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "sprite_renderer.h"

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Snake {
public:
    Snake(unsigned int screen_width, unsigned int screen_height);

    void draw(SpriteRenderer &renderer);
    void move();
    void grow();
    void set_direction(Direction dir);

    
private:
    std::vector<glm::vec2> segments;
    Direction current_direction;

    bool check_collision();
};
