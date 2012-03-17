#include "FireSpell.h"

FireSpell::FireSpell(int x, int y, float delta) : Spell(x, y, delta)
{
    sprite.SetTexture(rm.getImage("fire.png"));
    animation = thor::FrameAnimation::Create();
    for(int i = 0; i < 8*16; i+=16)
        animation->AddFrame(1.f, sf::IntRect(i, 0, 16, 16));

    animator.AddAnimation("animation", animation, sf::Seconds(0.5));
    animator.PlayAnimation("animation", true);

}

void FireSpell::onHit()
{
    destroyed = true;
}

FireSpell::~FireSpell()
{
    //dtor
}
