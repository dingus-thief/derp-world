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

    private:
        thor::DirectionalEmitter::Ptr emitter;
        thor::Emitter::ZonePtr zone;
};

#endif // FIRESPELL_H
