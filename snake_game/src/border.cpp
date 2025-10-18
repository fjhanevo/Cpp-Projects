#include "border.h"
#include "config.h"

Border::Border(unsigned int width, unsigned int height) :
    width(width), height(height),
    border_texture(ResourceManager::get_texture("temp")),
    border_size(TILE_SIZE, TILE_SIZE),
    border_color(glm::vec3(0.6f, 0.3f, 0.0f))
{}

void Border::draw(SpriteRenderer &renderer)
{
    // draw top and bottom border rows
    for (unsigned int x = 0; x < this->width; x+= TILE_SIZE)
    {
        // top border
        renderer.draw_sprite(
            this->border_texture,
            glm::vec2(x, 0.0f),
            this->border_size,
            0.0f,
            this->border_color
        );

        renderer.draw_sprite(
            this->border_texture,
            glm::vec2(x, this->height - TILE_SIZE),
            this->border_size,
            0.0f,
            this->border_color
        );
    }

    // left and right border columns
    for (unsigned int y = 0; y < this->width; y += TILE_SIZE)
    {
        // left border
        renderer.draw_sprite(
            this->border_texture,
            glm::vec2(0.0f, y),
            this->border_size,
            0.0f,
            this->border_color
        );

        // right border
        renderer.draw_sprite(
            this->border_texture,
            glm::vec2(this->width - TILE_SIZE, y),
            this->border_size, 
            0.0f,
            this->border_color
        );
    }
}
