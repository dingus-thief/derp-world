#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>
#include "Globals.h"
#include "Hero.h"
#include "State.h"
#include "Level.h"
#include "GameoverState.h"
#include "LiveLostState.h"
#include <sstream>
#include <iostream>
#include "Constants.h"


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

        static GameState* Instance(sf::RenderWindow* window, StateManager* mgr)
        {
            if(gameState == NULL)
                gameState = new GameState(window, mgr);
            return gameState;
        }


    private:

        GameState(sf::RenderWindow* window, StateManager* mgr);

        void reset();

        Level* level;
        Hero* hero;
        sf::View view;
        int currentLvl;
        sf::Music music;

        static GameState* gameState;

};

#endif // GAMESTATE_H
