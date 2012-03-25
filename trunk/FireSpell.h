#ifndef FIRESPELL_H
#define FIRESPELL_H

#include "Spell.h"
#include "RandomEmitter.h"

class FireSpell : public Spell
{
    public:
        FireSpell(int x, int y, float delta);
        virtual ~FireSpell();
        void onHit();
        void update();
        Spell* clone(int x, int y, float delta);

    private:
        thor::DirectionalEmitter::Ptr emitter;
        RandomEmitter::Ptr onHitEmitter;
        thor::Emitter::ZonePtr zone;
};

#endif // FIRESPELL_H
