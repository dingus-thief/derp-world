#ifndef MENUSTATE_H
#define MENUSTATE_H
#include <SFML/Audio.hpp>
#include "Globals.h"
#include "State.h"
#include "Button.h"

class MenuState : public State
{
    public:
        MenuState(sf::RenderWindow* window);

        void handle();
        void update();
        void render();

    private:
        void clicked(float x, float y);
        void checkButtons(float x, float y);

        sf::RenderWindow* Window;
        sf::Sprite background;
        Button* playButton;
        Button* optionsButton;
        Button* quitButton;
        sf::Music matrix;
};

#endif // MENUSTATE_H
