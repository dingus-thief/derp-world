#include "Spell.h"

Spell::Spell(int x, int y, float delta, unsigned damage, unsigned manacost, spell spellType) : destroyed(false), delta(delta), damage(damage), manacost(manacost), spellType(spellType), hit(false)
{
    sprite.SetPosition(x, y);
}

Spell::~Spell()
{
    //dtor
}

void Spell::draw(sf::RenderWindow* window)
{
    if(!hit)
        window->Draw(sprite);
    system->Draw(*window);
}
