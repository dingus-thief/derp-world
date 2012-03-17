#ifndef SPELL_H
#define SPELL_H
#include "ResourceManager.h"
#include <Thor/Animation.hpp>
#include "Globals.h"

class Spell
{
    public:
        Spell(int x, int y, float delta);
        void update();
        void draw(sf::RenderWindow* window);
        sf::FloatRect getBounds(){return sprite.GetGlobalBounds();}
        virtual ~Spell();
        virtual void onHit() = 0;

        bool destroyed;

    protected:
        int x;
        int y;
        float delta;
        sf::Sprite sprite;
        thor::Animator animator;
        thor::FrameAnimation::Ptr animation;

};

#endif // SPELL_H
