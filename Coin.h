#ifndef COIN_H
#define COIN_H
#include <SFML/Graphics.hpp>
#include "Globals.h"

class Coin
{
        friend class Hero;

    public:
        Coin(int x, int y);
        ~Coin();
        bool taken;
        void draw(sf::RenderWindow* window);
        sf::FloatRect getBounds();
        void onHit();

    private:
        sf::Sprite sprite;
        sf::Sound sound;
};

#endif // COIN_H
