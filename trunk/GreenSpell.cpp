#include "GreenSpell.h"

GreenSpell::GreenSpell(int x, int y, float delta) : Spell(x, y, delta, 25, 23, spell::green)
{
    sprite.SetTexture(rm.getImage("green.png"));
    animation = thor::FrameAnimation::Create();
    for(int i = 0; i < 5*16; i+=17)
        animation->AddFrame(1.f, sf::IntRect(i, 0, 16, 16));

    animator.AddAnimation("animation", animation, sf::Seconds(0.3));
    animator.PlayAnimation("animation", true);

    particleImage.LoadFromFile("Data/Images/energyParticle.png");
    system = new thor::ParticleSystem(thor::ResourcePtr<sf::Texture>(&particleImage));
}

GreenSpell::~GreenSpell()
{
    //dtor
}

void GreenSpell::update()
{
    animator.Update(sf::Milliseconds(timeStep));
    animator.Animate(sprite);
    sprite.Move(delta, 0);
}

void GreenSpell::onHit()
{
    destroyed = true;
}
//HEHEH WAHCT      CCOOOOLLL HEEEE WOOOOOOWIE GEMAAAAN COOL!! MKLD!!! ma kga andere tileset gebruiken!!! kom we gaan een level maken FUUUCK ff doe maar rustig zenu :p
