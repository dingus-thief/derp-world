#include "Entity.h"

Entity::Entity(const std::string& name, int x, int y)
{
    sprite.SetTexture(rm.getImage(name));
    sprite.SetPosition(x, y);
    dir = LEFT;
    previousDir = LEFT;
    vely = 5;
}

Entity::~Entity()
{
    //dtor
}

void Entity::update(const std::vector<Tile>& tiles)
{
    if(dir == LEFT)
    {
        sprite.Move(-0.3, 0);
    }
    else if(dir == RIGHT)
    {
        sprite.Move(0.3, 0);
    }
}

void Entity::draw(sf::RenderWindow* window)
{
    window->Draw(sprite);
}
