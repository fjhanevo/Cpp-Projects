#pragma once
#include <glm/vec2.hpp>
class Player {
private:
    unsigned int health;
    glm::vec2 position;
    int velocity; 
    int width, height;
    unsigned int texture;
public:
    Player(int width, int height); 
    void update();
    void draw();
    void move(const glm::vec2 &direction);
    bool shoot(const int key); 
    void take_damage();
    int get_size() const;
    glm::vec2 get_position() const;
};

