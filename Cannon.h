#ifndef CANNON_H
#define CANNON_H
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <vector>

class Cannon
{
    friend class Hero;

public:
    Cannon(const sf::Sprite& sprite);
    ~Cannon();

    void update(std::list<Bullet*>& bullets);
    void draw(sf::RenderWindow* window);
    void reset();

private:
    sf::Clock bulletClock;
    sf::Sprite sprite;
};

#endif // CANNON_H
