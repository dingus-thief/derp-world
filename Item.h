#ifndef ITEM_H
#define ITEM_H
#include "Globals.h"

enum ItemType {healthPotion, manaPotion};

class Item
{
    public:
        Item(int x, int y, ItemType type);
        virtual ~Item();
        void draw(sf::RenderWindow* window);
        void onCollect();
        void reset();
        ItemType getType();
        sf::FloatRect getBounds();
        bool isCollected();

    private:
        sf::Sound collectSound;
        sf::Sprite sprite;
        ItemType type;
        bool collected;
};

#endif // ITEM_H
