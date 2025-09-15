#include "player.h"
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

Player::Player(glm::vec2 size, float speed)
    : health(MAX_HEALTH), position(0.0f,0.0f), velocity(0.0f, 0.0f),
      speed(speed), size(size), texture(0) 
{}

void Player::update(float delta_time)
{
    position += velocity * speed * delta_time; 
}

void Player::move(const glm::vec2 &direction) 
{
    velocity += direction;
}

void Player::shoot()
{
}

glm::vec2 Player::get_size() const
{
    return size;
}

glm::vec2 Player::get_position() const
{
    return position;
}
