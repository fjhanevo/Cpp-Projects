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
    void queue_direction(Direction dir);

    glm::vec2 get_head_position() const;
    Direction get_current_direction() const;
    Direction get_next_direction() const;
    int get_length() const;
    const std::vector<glm::vec2>& get_segments() const;

    
private:
    std::vector<glm::vec2> segments;
    Direction current_direction;
    Direction next_direction;

};
