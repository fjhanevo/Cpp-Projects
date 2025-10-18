#include "food.h"
#include "resource_manager.h"
#include "config.h"


Food::Food() : 
    is_active(false), 
    position(0.0f, 0.0f), 
    food_timer(0.0f),
    food_texture(ResourceManager::get_texture("temp"))
{}

void Food::draw(SpriteRenderer &renderer)
{
    glm::vec3 food_color = glm::vec3(0.8f, 0.0f, 0.0f);

    if (this->is_active)
    {
        renderer.draw_sprite(
            this->food_texture,
            this->position,
            glm::vec2(TILE_SIZE, TILE_SIZE),
            0.0f, 
            food_color
        );
    }
}

void Food::update(float dt)
{
    if (this->is_active)
    {
        this->food_timer -= dt;
        if (this->food_timer <= 0.0f)
        {
            this->is_active = false;
        }
    }
}

void Food::spawn(glm::vec2 position)
{
    this->position = position;
    this->food_timer = FOOD_TIME;
    this->is_active = true;
}
