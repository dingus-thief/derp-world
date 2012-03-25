#include <iostream>
#include "MenuState.h"

using namespace std;

class MenuState;

int main()
{
    sf::Image icon;
    sf::RenderWindow Window;
    Window.Create(sf::VideoMode(WIDTH, HEIGHT, 32), "Derp World", sf::Style::Close);
    Window.SetFramerateLimit(100);

    icon.LoadFromFile("Data/Images/Ball.png");
    Window.SetIcon(icon.GetWidth(), icon.GetHeight(), icon.GetPixelsPtr());
    Window.EnableVerticalSync(false);

    StateManager stateManager;

    stateManager.changeState(MenuState::Instance(&Window, &stateManager));
    // main loop
    while ( stateManager.running )
    {
        stateManager.handle();
        stateManager.update();
        stateManager.draw();
        Window.Display();
    }
    return 0;
}
