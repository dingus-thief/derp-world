#include "Cannon.h"

Cannon::Cannon(const sf::Sprite& sprite) : sprite(sprite)
{
    //ctor
}

Cannon::~Cannon()
{
    //dtor
}

void Cannon::draw(sf::RenderWindow* window)
{
    window->Draw(sprite);
}

void Cannon::update(std::list<Bullet*>& bullets)
{
    if(bulletClock.GetElapsedTime().AsMilliseconds() > 3000)
    {
        sf::FloatRect rect = sprite.GetGlobalBounds();
        bullets.push_back(new Bullet(rect.Left, rect.Top));
        bulletClock.Restart();
    }
}
