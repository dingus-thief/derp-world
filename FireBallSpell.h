#ifndef FIREBALLSPELL_H
#define FIREBALLSPELL_H
#include "RandomEmitter.h"
#include "Spell.h"


class FireBallSpell : public Spell
{
    public:
        FireBallSpell(int x, int y, float delta);
        virtual ~FireBallSpell();
        void onHit();
        void update();
        Spell* clone(int x, int y, float delta);

    private:
        thor::DirectionalEmitter::Ptr emitter;
        RandomEmitter::Ptr onHitEmitter;
        thor::Emitter::ZonePtr zone;
};

#endif // FIREBALLSPELL_H
