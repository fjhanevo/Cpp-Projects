#include "player.h"
#include <GLFW/glfw3.h>

constexpr int max_health = 100;
Player::Player(int width, int height)
    : health(max_health), position(0.0f,0.0f), velocity(10),
      width(width), height(height), texture(0) 
{}

void Player::update()
{
    position.x += velocity;
    position.y += velocity;
}

void Player::move(const glm::vec2 &direction) 
{
    position.x += direction.x * velocity;
    position.y += direction.y * velocity;
}

bool Player::shoot(const int key)
{
    if (key == GLFW_KEY_SPACE) return true;
    return false;
}

int Player::get_size() const
{
    return width*height;
}

glm::vec2 Player::get_position() const
{
    return position;
}
