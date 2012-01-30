#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>
#include "Globals.h"
#include "Hero.h"
#include "State.h"
#include "Level.h"
#include "GameoverState.h"
#include <sstream>
#include <iostream>


class GameState : public State
{
    public:
        ~GameState();
        void render();
        void update();
        void handle();

        void pause();
        void resume();

        void init();
        void cleanup();


        GameState(sf::RenderWindow* window, Game* game);

    private:

        void reset();

        Level* level;
        Hero* hero;
        sf::View view;
        int currentLvl;

};

#endif // GAMESTATE_H
