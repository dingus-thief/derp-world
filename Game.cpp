#include "Game.h"
#include <sstream>

Game::Game()
{
    Window.Create(sf::VideoMode(WIDTH, HEIGHT, 32), "Unnamed Platformer");
    Window.SetFramerateLimit(100);

    GameState* gState = new GameState(&Window);
    states.push_back(gState);

    MenuState* mState = new MenuState(&Window);
    states.push_back(mState);

    GameoverState* goState = new GameoverState(&Window);
    states.push_back(goState);

    icon.LoadFromFile("Data/Images/Ball.png");
    Window.SetIcon(icon.GetWidth(), icon.GetHeight(), icon.GetPixelsPtr());
    Window.EnableVerticalSync(false);
}

Game::~Game()
{
    //dtor
}

void Game::run()
{
    while(Window.IsOpen())
    {
        states[currentState]->handle();
        states[currentState]->update();
        states[currentState]->render();
    }
}
