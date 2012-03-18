#include "GreenSpell.h"

GreenSpell::GreenSpell(int x, int y, float delta) : Spell(x, y, delta, 25, 23)
{
    sprite.SetTexture(rm.getImage("green.png"));
    animation = thor::FrameAnimation::Create();
    for(int i = 0; i < 5*16; i+=17)
        animation->AddFrame(1.f, sf::IntRect(i, 0, 16, 16));

    animator.AddAnimation("animation", animation, sf::Seconds(0.3));
    animator.PlayAnimation("animation", true);
}

GreenSpell::~GreenSpell()
{
    //dtor
}

void GreenSpell::onHit()
{
    destroyed = true;
}
