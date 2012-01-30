#include "Coin.h"

Coin::Coin(const sf::Sprite& sprite) : taken(false), sprite(sprite)
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
