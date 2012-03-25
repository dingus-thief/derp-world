#include "Item.h"

Item::Item(int x, int y, ItemType type) : collected(false), type(type)
{
    sprite.SetPosition(x, y);
    collectSound.SetBuffer(rm.getSoundBuffer("pickup.wav"));

    switch(type)
    {
        case healthPotion:
            sprite.SetTexture(rm.getImage("healthPotion.png"));
            break;
        case manaPotion:
            sprite.SetTexture(rm.getImage("manaPotion.png"));
            break;
    }
}

Item::~Item()
{
    //dtor
}

bool Item::isCollected()
{
    return collected;
}

ItemType Item::getType()
{
    return type;
}

void Item::reset()
{
    collected = false;
}

sf::FloatRect Item::getBounds()
{
    return sprite.GetGlobalBounds();
}

void Item::draw(sf::RenderWindow* window)
{
    if(!collected)
    {
        window->Draw(sprite);
    }
}

void Item::onCollect()
{
    collectSound.Play();
    collected = true;
}
