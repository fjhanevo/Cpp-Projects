#include "snake.h"
#include "resource_manager.h"
#include "sprite_renderer.h"

Snake::Snake(unsigned int screen_width, unsigned int screen_height)
{
    this->direction = Direction::RIGHT;

    this->segments.clear();

    // create snake in the centre of the screen
    glm::vec2 snake_head = { 
        floor(screen_width / (2.0f * SEGMENT_SIZE)) * SEGMENT_SIZE,
        floor(screen_height / (2.0f * SEGMENT_SIZE)) * SEGMENT_SIZE 
    };
    this->segments.push_back(snake_head);

    // add some more segments just to test
    this->segments.push_back({snake_head.x, snake_head.y - SEGMENT_SIZE});
    this->segments.push_back({snake_head.x, snake_head.y - (2*SEGMENT_SIZE)});

}


void Snake::draw(SpriteRenderer &renderer)
{
    Texture2D snake_head_tex = ResourceManager::get_texture("temp");
    Texture2D snake_body_tex = ResourceManager::get_texture("temp");
    
    glm::vec3 snake_head_color = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 snake_body_color = glm::vec3(0.2f, 0.2f, 0.2f);
    float tile_size = 20.0f;
    glm::vec2 snake_size = glm::vec2(tile_size, tile_size);

    if (!segments.empty())
    {
        // draw head first
        renderer.draw_sprite(
            snake_head_tex, 
            segments[0],
            snake_size,
            0.0f,   // TODO: Make head rotate based on Direction
            snake_head_color
        );

        // draw rest of the body
        for (size_t i = 1; i < segments.size(); ++i)
        {
            renderer.draw_sprite(
                snake_body_tex,
                segments[i],
                snake_size,
                0.0f,
                snake_body_color
            );
        }
    }
}

void Snake::move()
// updates head position and shifts the body backwards
{
    for (size_t i = this->segments.size() - 1; i > 0; i--)
        this->segments[i] = this->segments[i-1];

    switch (this->direction)
    {
        case Direction::UP:     this->segments[0].y -= SEGMENT_SIZE; break;
        case Direction::DOWN:   this->segments[0].y += SEGMENT_SIZE; break;
        case Direction::LEFT:   this->segments[0].x -= SEGMENT_SIZE; break;
        case Direction::RIGHT:  this->segments[0].x += SEGMENT_SIZE; break;
    }
}

void Snake::set_direction(Direction dir)
{
    this->direction = dir;
}

Direction Snake::get_direction() const
{
    return this->direction;
}
