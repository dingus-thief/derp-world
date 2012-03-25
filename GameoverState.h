#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H
#include "Globals.h"
#include "Button.h"
#include "State.h"


class GameoverState : public State
{
    public:
        ~GameoverState();
        void init();
        void cleanup();

        void update();
        void render();
        void handle();

        void pause() {};
        void resume() {};

        static GameoverState* Instance(sf::RenderWindow* window, StateManager* mgr)
        {
            if(gameoverState == NULL)
                gameoverState = new GameoverState(window, mgr);
            return gameoverState;
        }

    private:
        GameoverState(sf::RenderWindow* window, StateManager* mgr);

        sf::Text gameoverText;
        sf::Text scoreText;
        Button* quitButton;
        Button* playAgainButton;

        static GameoverState* gameoverState;

        void checkButtons(float x, float y);
        void clicked(float x, float y);
};

#endif // GAMEOVERSTATE_H
