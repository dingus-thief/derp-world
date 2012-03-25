#ifndef NEWGAMESTATE_H
#define NEWGAMESTATE_H

#include "State.h"


class NewGameState : public State
{
    public:
        NewGameState(sf::RenderWindow* window, StateManager* mgr);
        virtual ~NewGameState();
    protected:
    private:
};

#endif // NEWGAMESTATE_H
