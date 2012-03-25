#ifndef BULLET_H
#define BULLET_H
#include "Globals.h"
#include <list>

class Bullet
{
    public:
        Bullet(int x, int y, int delta);
        ~Bullet();
        void draw(sf::RenderWindow* window);
        void update();
        float distance;
        int delta;
        bool dead;
        sf::Sprite sprite;

    private:

};

#endif // BULLET_H
