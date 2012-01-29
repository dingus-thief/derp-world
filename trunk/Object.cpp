#include "Object.h"

Object::Object(const sf::Sprite& sprite) : sprite(sprite)
{
    //ctor
}

Object::~Object()
{
    //dtor
}

void Object::draw(sf::RenderWindow* window)
{
    window->Draw(sprite);
}
