#ifndef LIVELOSTSTATE_H
#define LIVELOSTSTATE_H
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Button.h"
#include <cstdlib>


class LiveLostState : public State
{
    public:
        void handle();
        void update();
        void render();

        void pause();
        void resume();

        void init();
        void cleanup();

        static LiveLostState* Instance(sf::RenderWindow* window, StateManager* mgr, int livesLeft)
       	{
       	    if(liveLostState == NULL)
                liveLostState = new LiveLostState(window, mgr);
            liveLostState->livesLeft = livesLeft;

            return liveLostState;
        }

        int livesLeft;

    private:
        LiveLostState(sf::RenderWindow* window, StateManager* mgr);

        void clicked(float x, float y);
        void checkButtons(float x, float y);

        sf::Sprite background;
        Button* restartButton;
        sf::Text text;


        bool goingDown;
        float pixelsGoneDown;

        static LiveLostState* liveLostState;
};

#endif // LIVELOSTSTATE_H
