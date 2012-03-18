#include "IceSpell.h"

IceSpell::IceSpell(int x, int y, float delta) : Spell(x, y, delta, 20, 9)
{
    sprite.SetTexture(rm.getImage("ice.png"));
    animation = thor::FrameAnimation::Create();
        animation->AddFrame(1.f, sf::IntRect(0, 0, 12, 16));
        animation->AddFrame(1.f, sf::IntRect(13, 0, 12, 16));

    animator.AddAnimation("animation", animation, sf::Seconds(0.3));
    animator.PlayAnimation("animation", true);

}

IceSpell::~IceSpell()
{
    //dtor
}

void IceSpell::onHit()
{
    destroyed = true;
}
