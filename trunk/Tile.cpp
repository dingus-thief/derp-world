#include "Tile.h"
#include "Globals.h"

Tile::Tile(const sf::Sprite& sprite, bool transparent, bool platform, bool kill) : transparent(transparent), sprite(sprite), platform(platform), kill(kill)
{

}

Tile::~Tile()
{
    //dtor
}

void Tile::draw(sf::RenderWindow* window)
{
    window->Draw(sprite);
}

Tile* Tile::clone()
{
    return new Tile(*this);
}

sf::Vector2f Tile::getCenterPoint()
{
    return sf::Vector2f(sprite.GetGlobalBounds().Top + sprite.GetGlobalBounds().Height/2, sprite.GetGlobalBounds().Left + sprite.GetGlobalBounds().Width/2);
}

sf::FloatRect Tile::getBounds()
{
    return sprite.GetGlobalBounds();
}
