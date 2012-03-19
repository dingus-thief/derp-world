#ifndef GREENSPELL_H
#define GREENSPELL_H

#include "Spell.h"


class GreenSpell : public Spell
{
    public:
        GreenSpell(int x, int y, float delta);
        ~GreenSpell();
        void onHit();
        void update();
    private:
};

#endif // GREENSPELL_H
