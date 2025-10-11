#pragma once
#include <glm/glm.hpp>
#include "sprite_renderer.h"

const float FOOD_TIME = 10.0f;

class Food
{
public:
    Food();

    bool is_active;
    glm::vec2 position;

    void draw(SpriteRenderer &renderer);
    void update(float dt);
    void spawn(glm::vec2 position);
private:
    float food_timer;
};
