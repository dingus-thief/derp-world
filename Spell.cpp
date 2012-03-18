#include "Spell.h"

Spell::Spell(int x, int y, float delta, unsigned damage, unsigned manacost) : destroyed(false), delta(delta), damage(damage), manacost(manacost)
{
    sprite.SetPosition(x, y);
}

void Spell::update()
{
    animator.Update(sf::Milliseconds(timeStep));
    animator.Animate(sprite);
    sprite.Move(delta, 0);
}

Spell::~Spell()
{
    //dtor
}

void Spell::draw(sf::RenderWindow* window)
{
    window->Draw(sprite);
}
