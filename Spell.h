#ifndef SPELL_H
#define SPELL_H
#include "ResourceManager.h"
#include <Thor/Animation.hpp>
#include <Thor/Particles.hpp>
#include <Thor/Geometry.hpp>
#include "Globals.h"
#include "Constants.h"

class Spell
{
public:
    Spell(int x, int y, float delta, unsigned damage, unsigned manacost, spell spellType);

    void draw(sf::RenderWindow* window);
    spell type()
    {
        return spellType;
    }
    sf::FloatRect getBounds()
    {
        return sprite.GetGlobalBounds();
    }
    virtual ~Spell();
    virtual void onHit() = 0;
    virtual void update() = 0;
    virtual Spell* clone(int x, int y, float delta) = 0;

    bool destroyed;
    bool hit;
    unsigned damage;
    unsigned manacost;

protected:
    int x;
    int y;
    float delta;
    spell spellType;


    sf::Sprite sprite;
    thor::Animator animator;
    thor::FrameAnimation::Ptr animation;
    thor::ParticleSystem* system;
    sf::Texture particleImage;

};

#endif // SPELL_H
