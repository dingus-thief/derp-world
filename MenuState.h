#ifndef MENUSTATE_H
#define MENUSTATE_H
#include <SFML/Audio.hpp>
#include "Globals.h"
#include "GameState.h"
#include "Button.h"

class MenuState : public State
{
    public:
        void handle();
        void update();
        void render();

        void pause() {};
        void resume() {};

        void init();
        void cleanup();

        static MenuState* Instance(sf::RenderWindow* window, StateManager* mgr)
       	{
       	    if(menuState == NULL)
                menuState = new MenuState(window, mgr);

            return menuState;
        }

    private:
        MenuState(sf::RenderWindow* window, StateManager* mgr);

        void clicked(float x, float y);
        void checkButtons(float x, float y);

        sf::Sprite background;
        Button* playButton;
        Button* optionsButton;
        Button* quitButton;

        static MenuState* menuState;
};

#endif // MENUSTATE_H
