#ifndef GAME_H
#define GAME_H
#include <vector>
#include "Globals.h"
#include <SFML/Graphics.hpp>

class State;

class Game
{
    public:
        Game();
        ~Game();
        void draw();
        void handle();
        void update();

        void changeState(State* state);
        void pushState(State* state);
        void popState();

        bool running;

    private:
        std::vector<State*> states;

};

#endif // GAME_H
