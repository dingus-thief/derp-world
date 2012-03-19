#ifndef ICESPELL_H
#define ICESPELL_H

#include "Spell.h"


class IceSpell : public Spell
{
    public:
        IceSpell(int x, int y, float delta);
        ~IceSpell();
        void onHit();
        void update();

    private:
        thor::DirectionalEmitter::Ptr emitter;
        thor::Emitter::ZonePtr zone;
};

#endif // ICESPELL_H
