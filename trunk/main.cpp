#include <iostream>
#include "Game.h"
#include "MenuState.h"

using namespace std;

class MenuState;

int main()
{
    sf::Image icon;
    sf::RenderWindow Window;
    Window.Create(sf::VideoMode(WIDTH, HEIGHT, 32), "Derp World");
    Window.SetFramerateLimit(100);

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
