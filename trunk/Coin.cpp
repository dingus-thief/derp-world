#include "Coin.h"

Coin::Coin(int x, int y) : taken(false)
{
    sprite.SetTexture(rm.getImage("coin.png"));
    sprite.SetPosition(x, y);
    sound.SetBuffer(rm.getSoundBuffer("cointaken2.wav"));
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

sf::FloatRect Coin::getBounds()
{
    return sprite.GetGlobalBounds();
}

void Coin::onHit()
{
    sound.Play();
}
