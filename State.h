#ifndef STATE_H
#define STATE_H
#include "StateManager.h"

class State
{
    public:
        State(sf::RenderWindow* window, StateManager* mgr);
        virtual ~State() {};
        virtual void handle() = 0;
        virtual void update() = 0;
        virtual void render() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void init() = 0;
        virtual void cleanup() = 0;

        bool drawOnTop;

    protected:
        StateManager* stateManager;
        sf::RenderWindow* window;

    private:
};

#endif // STATE_H
