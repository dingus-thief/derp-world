#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H
#include "Globals.h"
#include "Button.h"
#include "State.h"


class GameoverState : public State
{
    public:
        ~GameoverState();

        void update();
        void render();
        void handle();

        void pause(){};
        void resume(){};

        GameoverState(sf::RenderWindow* window, Game* game);

    private:
        static GameoverState* m_GameoverState;

        bool running;

        sf::Text gameoverText;
        sf::Text scoreText;
        Button* quitButton;
        Button* playAgainButton;

        void checkButtons(float x, float y);
        void clicked(float x, float y);



};

#endif // GAMEOVERSTATE_H
