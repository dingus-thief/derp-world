#include <iostream>
#include "Game.h"
#include "MenuState.h"

using namespace std;

class MenuState;

int main()
{
    sf::Image icon;
    sf::RenderWindow Window;
    Window.Create(sf::VideoMode(WIDTH, HEIGHT, 32), "Unnamed Platformer");
    Window.SetFramerateLimit(100);

    /*GameState* gState = new GameState(&Window);
    states.push_back(gState);

    MenuState* mState = new MenuState(&Window);
    states.push_back(mState);

    GameoverState* goState = new GameoverState(&Window);
    states.push_back(goState);*/

    icon.LoadFromFile("Data/Images/Ball.png");
    Window.SetIcon(icon.GetWidth(), icon.GetHeight(), icon.GetPixelsPtr());
    Window.EnableVerticalSync(false);

    Game game;
    game.changeState(new MenuState(&Window, &game));
    // main loop
	while ( game.running )
	{
		game.handle();
		game.update();
		game.draw();
	}
    return 0;
}
