#include "snake.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "config.h"

Snake::Snake(unsigned int screen_width, unsigned int screen_height)
: current_direction(Direction::DOWN), next_direction(Direction::DOWN)
{

    this->segments.clear();

    // create snake in the centre of the screen
    glm::vec2 snake_head = { 
        floor(screen_width / (2.0f * TILE_SIZE)) * TILE_SIZE,
        floor(screen_height / (2.0f * TILE_SIZE)) * TILE_SIZE 
    };
    this->segments.push_back(snake_head);
}

void Snake::draw(SpriteRenderer &renderer)
{
    Texture2D snake_head_tex = ResourceManager::get_texture("temp");
    Texture2D snake_body_tex = ResourceManager::get_texture("temp");
    Texture2D snake_tail_tex = ResourceManager::get_texture("temp");
    
    glm::vec3 snake_head_color = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 snake_body_color = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 snake_tail_color = glm::vec3(0.8f, 0.2f, 0.2f);
    glm::vec2 snake_size = glm::vec2(TILE_SIZE, TILE_SIZE);

    if (segments.empty())
        return;
    
    // draw head first
    renderer.draw_sprite(
        snake_head_tex, 
        segments[0],
        snake_size,
        0.0f,   // TODO: Make head rotate based on Direction
        snake_head_color
    );

    // draw rest of the body
    for (size_t i = 1; i < segments.size() - 1; ++i)
    {
        renderer.draw_sprite(
            snake_body_tex,
            segments[i],
            snake_size,
            0.0f,
            snake_body_color
        );
    }
    // draw the tail
    if (this->segments.size() > 1)
        renderer.draw_sprite(
            snake_tail_tex,
            segments[segments.size()-1],
            snake_size,
            0.0f,
            snake_tail_color
        );
    
}

void Snake::move()
// updates head position and shifts the body backwards
{
    for (size_t i = this->segments.size() - 1; i > 0; i--)
        this->segments[i] = this->segments[i-1];

    switch (this->current_direction)
    {
        case Direction::UP:     this->segments[0].y -= TILE_SIZE; break;
        case Direction::DOWN:   this->segments[0].y += TILE_SIZE; break;
        case Direction::LEFT:   this->segments[0].x -= TILE_SIZE; break;
        case Direction::RIGHT:  this->segments[0].x += TILE_SIZE; break;
    }
}

void Snake::grow()
{
    if (!this->segments.empty())
        this->segments.push_back(this->segments.back());
}

void Snake::set_direction(Direction dir)
{
    this->current_direction = dir;
}

void Snake::queue_direction(Direction dir)
{
    this->next_direction = dir;
}

Direction Snake::get_current_direction() const
{
    return this->current_direction;
}

Direction Snake::get_next_direction() const
{
    return this->next_direction;
}

glm::vec2 Snake::get_head_position() const
{
    return this->segments[0];
}

int Snake::get_length() const
{
    return this->segments.size();
}

const std::vector<glm::vec2>& Snake::get_segments() const
{
    return this->segments;
}
