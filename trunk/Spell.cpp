#include "Spell.h"

Spell::Spell(int x, int y, float delta, unsigned damage, unsigned manacost, spell spellType) : destroyed(false), delta(delta), damage(damage), manacost(manacost), spellType(spellType)
{
    sprite.SetPosition(x, y);
}

Spell::~Spell()
{
    //dtor
}

void Spell::draw(sf::RenderWindow* window)
{
    system->Draw(*window);
    window->Draw(sprite);
}
