#pragma once
#include <glm/vec2.hpp>
class Player {
private:
    unsigned int health;
    glm::vec2 position;
    glm::vec2 velocity; 
    float speed;
    glm::vec2 size;;
    unsigned int texture;
public:
    static constexpr int MAX_HEALTH = 100;

    Player(glm::vec2 size, float speed); 
    void update(float delta_time);
    void draw();

    void move(const glm::vec2 &direction);
    void shoot(); 
    void take_damage();

    glm::vec2 get_size() const;
    glm::vec2 get_position() const;
};

