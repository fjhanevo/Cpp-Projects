#pragma once
#include "resource_manager.h"
#include "sprite_renderer.h"
#include <glm/glm.hpp>

class Border
{
public:
    Border(unsigned int width, unsigned int height);
    void draw(SpriteRenderer &renderer);
private:
    unsigned int width, height;
    glm::vec2 border_size;
    glm::vec3 border_color;
    Texture2D &border_texture;
};
