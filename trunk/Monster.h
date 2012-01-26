#ifndef MONSTER_H
#define MONSTER_H
#include "Globals.h"
#include <SFML/Graphics.hpp>

class Monster
{
    public:
        Monster(std::string name);
        ~Monster();
        virtual void update(int frameTime) = 0;
        void draw(sf::RenderWindow* window);
        bool dead;
    private:
        sf::Sprite sprite;

};

#endif // MONSTER_H
