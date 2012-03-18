#ifndef ICESPELL_H
#define ICESPELL_H

#include "Spell.h"


class IceSpell : public Spell
{
    public:
        IceSpell(int x, int y, float delta);
        ~IceSpell();
        void onHit();

    private:
};

#endif // ICESPELL_H
