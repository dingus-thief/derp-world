#include "FireSpell.h"

FireSpell::FireSpell(int x, int y, float delta) : Spell(x, y, delta, 10, 5, spell::fire)
{
    sprite.SetTexture(rm.getImage("fire.png"));
    sprite.SetTextureRect(sf::IntRect(0, 0, 16, 16));
    animation = thor::FrameAnimation::Create();
    for(int i = 0; i < 8*16; i+=16)
        animation->AddFrame(1.f, sf::IntRect(i, 0, 16, 16));

    animator.AddAnimation("animation", animation, sf::Seconds(0.3));
    animator.PlayAnimation("animation", true);

    particleImage.LoadFromFile("Data/Images/fireParticle.png");
    system = new thor::ParticleSystem(thor::ResourcePtr<sf::Texture>(&particleImage));

    emitter = thor::DirectionalEmitter::Create(15, sf::Seconds(0.3));
    emitter->SetParticleVelocity(sf::Vector2f(-1, 0));

    onHitEmitter = RandomEmitter::Create(200, sf::Milliseconds(200));

    const thor::ColorGradient gradient = thor::CreateGradient(sf::Color::Red)(1)(sf::Color::Transparent);
    system->AddAffector(thor::ColorAffector::Create(gradient));

    system->AddEmitter(emitter);
}

void FireSpell::update()
{
    if(!system->ContainsEmitter(emitter) && !system->ContainsEmitter(onHitEmitter))
        destroyed = true;

    animator.Update(sf::Milliseconds(timeStep));
    animator.Animate(sprite);

    emitter->SetEmissionZone(thor::Emitter::ZonePtr(new thor::Rectangle(sprite.GetGlobalBounds())));
    system->Update(sf::Milliseconds(timeStep));

    sprite.Move(delta, 0);
}


void FireSpell::onHit()
{
    hit = true;
    system->ClearEmitters();
    system->AddEmitter(onHitEmitter, sf::Milliseconds(200));
    sf::FloatRect rect = sprite.GetGlobalBounds();
    if(delta < 0) //left
        rect.Left -= 16;
    onHitEmitter->SetEmissionZone(thor::Emitter::ZonePtr(new thor::Rectangle(rect)));
}

FireSpell::~FireSpell()
{
    delete system;
}
