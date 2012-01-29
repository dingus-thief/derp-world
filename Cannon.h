#ifndef CANNON_H
#define CANNON_H
#include <SFML/System/Clock.hpp>
#include "Object.h"


class Cannon : public Object
{
    public:
        Cannon(const sf::Sprite& sprite);
        ~Cannon();

        void update(){};

    private:
        sf::Clock bulletClock;
};

#endif // CANNON_H
