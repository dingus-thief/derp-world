#include "Bullet.h"

Bullet::Bullet(int x, int y) : distance(0), dead(false)
{
    sprite.SetPosition(x, y);
    sprite.SetTexture(rm.getImage("Bullet.png"));
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::draw(sf::RenderWindow* window)
{
    window->Draw(sprite);
}

void Bullet::update()
{
    sprite.Move(-0.5, 0);
    distance += 0.5;
    if(distance > 350)
        dead = true;
}
