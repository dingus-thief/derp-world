#include "Monster.h"

Monster::Monster(std::string name)
{
    sprite.SetTexture(rm.getImage(name));
}

Monster::~Monster()
{
    //dtor
}

void Monster::draw(sf::RenderWindow* window)
{
    window->Draw(sprite);
}
