#ifndef GAME_H
#define GAME_H
#include <vector>
#include "State.h"
#include "GameState.h"
#include "MenuState.h"
#include "GameoverState.h"
#include "Globals.h"
#include <SFML/Graphics.hpp>

class Game
{
    public:
        Game();
        ~Game();
        void run();

    private:
        sf::RenderWindow Window;
        sf::Image icon;
        std::vector<State*> states;

};

#endif // GAME_H
