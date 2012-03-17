#ifndef FIRESPELL_H
#define FIRESPELL_H

#include "Spell.h"


class FireSpell : public Spell
{
    public:
        FireSpell(int x, int y, float delta);
        virtual ~FireSpell();
        void onHit();
    protected:
    private:
};

#endif // FIRESPELL_H
