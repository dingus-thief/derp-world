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


class GameState : public State
{
    public:
        GameState(sf::RenderWindow* window);
        void render();
        void update();
        void handle();

    private:
        void updateText();
        void reset();

        Level* level;
        Hero* hero;
        sf::View view;
        sf::RenderWindow* Window;
        sf::Sprite background;
        sf::Sprite heart;
        sf::Text scoreText;
        int currentLvl;
};

#endif // GAMESTATE_H
