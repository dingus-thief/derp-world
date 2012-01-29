#ifndef COIN_H
#define COIN_H
#include <SFML/Graphics.hpp>

class Coin
{
    friend class Hero;

    public:
        Coin(const sf::Sprite& sprite);
        ~Coin();
        bool taken;
        void draw(sf::RenderWindow* window);

    private:
        sf::Sprite sprite;
        sf::Clock aniClock;
};

#endif // COIN_H
