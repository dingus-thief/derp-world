#ifndef MOVINGTILE_H
#define MOVINGTILE_H
#include "Constants.h"
#include "Tile.h"
#include <list>


class MovingTile : public Tile
{
public:
    MovingTile(const sf::Sprite& sprite, bool transparent, bool platform, bool kill, float x, float y);
    ~MovingTile();

    void update(std::list<sf::FloatRect> blocks);
    sf::Vector2f getSpeed();

private:
    float x;
    float y;
};

#endif // MOVINGTILE_H
