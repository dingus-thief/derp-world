#include "Tile.h"
#include "Globals.h"

Tile::Tile(const sf::Sprite& sprite, bool solid, bool jumpThrough) : solid(solid), sprite(sprite), jumpThrough(jumpThrough)
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
