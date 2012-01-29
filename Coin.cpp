#include "Coin.h"

Coin::Coin(const sf::Sprite& sprite) : sprite(sprite), taken(false)
{
    //ctor
}

Coin::~Coin()
{
    //dtor
}

void Coin::draw(sf::RenderWindow* window)
{
    if(!taken)
        window->Draw(sprite);
}
