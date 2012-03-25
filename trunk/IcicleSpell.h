#ifndef ICICLESPELL_H
#define ICICLESPELL_H
#include "RandomEmitter.h"
#include "Spell.h"


class IcicleSpell : public Spell
{
    public:
        IcicleSpell(int x, int y, float delta);
        virtual ~IcicleSpell();
        void onHit();
        void update();
        Spell* clone(int x, int y, float delta);

    private:
        thor::DirectionalEmitter::Ptr emitter;
        thor::Emitter::ZonePtr zone;
        RandomEmitter::Ptr onHitEmitter;
};

#endif // ICICLESPELL_H
