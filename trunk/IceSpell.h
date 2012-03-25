#ifndef ICESPELL_H
#define ICESPELL_H
#include "RandomEmitter.h"
#include "Spell.h"


class IceSpell : public Spell
{
    public:
        IceSpell(int x, int y, float delta);
        ~IceSpell();
        void onHit();
        void update();
        Spell* clone(int x, int y, float delta);

    private:
        thor::DirectionalEmitter::Ptr emitter;
        thor::Emitter::ZonePtr zone;
        RandomEmitter::Ptr onHitEmitter;
};

#endif // ICESPELL_H
