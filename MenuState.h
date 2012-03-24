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

    MenuState(sf::RenderWindow* window, Game* game);

private:

    void clicked(float x, float y);
    void checkButtons(float x, float y);

    sf::Sprite background;
    Button* playButton;
    Button* optionsButton;
    Button* quitButton;
    sf::Music matrix;
};

#endif // MENUSTATE_H
