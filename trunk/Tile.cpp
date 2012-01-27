#include "Tile.h"
#include "Globals.h"

Tile::Tile(const sf::Sprite& sprite, bool transparent, bool platform) : transparent(transparent), sprite(sprite), platform(platform)
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
