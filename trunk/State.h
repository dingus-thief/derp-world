#ifndef STATE_H
#define STATE_H
#include "Game.h"

class State
{
    public:
        State(Game* game, sf::RenderWindow* window);
        virtual ~State(){};
        virtual void handle() = 0;
        virtual void update() = 0;
        virtual void render() = 0;

        virtual void pause() = 0;
        virtual void resume() = 0;

        virtual void init(){};
        virtual void cleanup(){};

    protected:
        Game* game;
        sf::RenderWindow* window;


    private:
};

#endif // STATE_H
