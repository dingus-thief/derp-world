#include "MovingTile.h"

MovingTile::MovingTile(const sf::Sprite& sprite, bool transparent, bool platform, bool kill, float x, float y) : Tile(sprite,transparent,platform,kill), x(x*tsAdjuster), y(y*tsAdjuster)
{
    //ctor
}

MovingTile::~MovingTile()
{
    //dtor
}

void MovingTile::update(std::list<sf::FloatRect> blocks)
{
    sprite.Move(x, y);
    sf::FloatRect rect1 = sprite.GetGlobalBounds();
    for(auto itr = blocks.begin(); itr != blocks.end(); itr++)
    {
        if(rect1.Intersects(*itr))
        {
            x = -x;
            y = -y;
        }
    }
}

sf::Vector2f MovingTile::getSpeed()
{
    return sf::Vector2f(x, y);
}
