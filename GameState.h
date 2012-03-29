#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
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

        GameState(sf::RenderWindow* window, StateManager* mgr);

        static GameState* Instance(sf::RenderWindow* window, StateManager* mgr, const std::string& levelFile)
        {
            /*if(gameState == NULL)
                gameState = new GameState(window, mgr);*/
            GameState* newstate = new GameState(window, mgr);
            newstate->levelPath = levelFile;
            return newstate;
        }


    private:
        void reset();
        Level* level;
        Hero* hero;
        HUD* hud;
        sf::View view;
        int currentLvl;
        sf::Music* music;
        std::string levelPath;
        sf::Sprite loadingSprite;

        static GameState* gameState;

};

#endif // GAMESTATE_H
