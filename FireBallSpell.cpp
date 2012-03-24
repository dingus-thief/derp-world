#include "FireBallSpell.h"

FireBallSpell::FireBallSpell(int x, int y, float delta) : Spell(x, y, delta, 10, 5, spell::fire)
{
    sprite.SetTexture(rm.getImage("FIREBALL.png"));
    animation = thor::FrameAnimation::Create();
    if(delta > 0) //right
        animation->AddFrame(1.f, sf::IntRect(24, 0, 24, 16));
    else //left
        animation->AddFrame(1.f, sf::IntRect(0, 0, 24, 16));

    animator.AddAnimation("animation", animation, sf::Seconds(0.3));
    animator.PlayAnimation("animation", true);

    particleImage.LoadFromFile("Data/Images/fireParticle.png");
    system = new thor::ParticleSystem(thor::ResourcePtr<sf::Texture>(&particleImage));

    emitter = thor::DirectionalEmitter::Create(15, sf::Seconds(0.3));
    emitter->SetParticleVelocity(sf::Vector2f(-1, 0));

    onHitEmitter = RandomEmitter::Create(200, sf::Milliseconds(200));

    system->AddAffector(thor::FadeOutAffector::Create(1.f));

    system->AddEmitter(emitter);
}

Spell* FireBallSpell::clone(int x, int y, float delta)
{
    return new FireBallSpell(x, y, delta);
}

void FireBallSpell::update()
{
    if(!system->ContainsEmitter(emitter) && !system->ContainsEmitter(onHitEmitter))
        destroyed = true;

    animator.Update(sf::Milliseconds(timeStep));
    animator.Animate(sprite);

    emitter->SetEmissionZone(thor::Emitter::ZonePtr(new thor::Rectangle(sprite.GetGlobalBounds())));
    system->Update(sf::Milliseconds(timeStep));

    sprite.Move(delta, 0);
}


void FireBallSpell::onHit()
{
    hit = true;
    system->ClearEmitters();
    system->AddEmitter(onHitEmitter, sf::Milliseconds(200));
    sf::FloatRect rect = sprite.GetGlobalBounds();
    if(delta < 0) //left
        rect.Left -= 16;
    onHitEmitter->SetEmissionZone(thor::Emitter::ZonePtr(new thor::Rectangle(rect)));
}

FireBallSpell::~FireBallSpell()
{
    delete system;
}
