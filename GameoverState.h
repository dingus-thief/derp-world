#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H
#include "Globals.h"
#include "Button.h"
#include "State.h"


class GameoverState : public State
{
    public:
        GameoverState(sf::RenderWindow* window);
        ~GameoverState();
        void run();


    private:
        bool running;

        sf::RenderWindow* window;
        sf::Text gameoverText;
        sf::Text scoreText;
        Button* quitButton;
        Button* playAgainButton;

        void checkButtons(float x, float y);
        void clicked(float x, float y);

        void update();
        void render();
        void handle();

};

#endif // GAMEOVERSTATE_H
