#include "Spell.h"

Spell::Spell(int x, int y, float delta, unsigned damage, unsigned manacost, spell spellType) : destroyed(false), delta(delta*tsAdjuster), damage(damage), manacost(manacost), spellType(spellType), hit(false)
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
    if(!hit)
        window->Draw(sprite);
}
