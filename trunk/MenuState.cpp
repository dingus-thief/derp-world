#include "MenuState.h"

MenuState* MenuState::menuState = NULL;

MenuState::MenuState(sf::RenderWindow* window, StateManager* mgr) : State(window, mgr)
{
    background.SetTexture(rm.getImage("menuBackground.png"));
    newGameButton = new Button("New Game",0, 100);
    newGameButton->center(0, WIDTH);
    optionsButton = new Button("Options", 0, 200);
    quitButton = new Button("Quit", 0, 300);
}

void MenuState::init()
{

}

void MenuState::cleanup()
{

}

void MenuState::update()
{

}

void MenuState::handle()
{
    sf::Event Event;
    while (window->PollEvent(Event))
    {
        switch (Event.Type)
        {
            case sf::Event::Closed:
                window->Close();
                break;
            case sf::Event::MouseMoved:
                checkButtons(window->ConvertCoords(sf::Mouse::GetPosition(*window).x, 0).x, window->ConvertCoords(0, sf::Mouse::GetPosition(*window).y).y);
                break;
            case sf::Event::MouseButtonPressed:
                if(Event.MouseButton.Button == sf::Mouse::Left)
                    clicked(window->ConvertCoords(sf::Mouse::GetPosition(*window).x, 0).x, window->ConvertCoords(0, sf::Mouse::GetPosition(*window).y).y);
                break;
            default:
                break;
        }
    }
}

void MenuState::checkButtons(float x, float y)
{
    newGameButton->checkHL(x, y);
    optionsButton->checkHL(x, y);
    quitButton->checkHL(x, y);
}

void MenuState::clicked(float x, float y)
{
    if(newGameButton->isClicked(x, y))
        stateManager->pushState(NewGameState::Instance(window, stateManager));
    if(quitButton->isClicked(x, y))
        window->Close();
}

void MenuState::render()
{
    window->SetView(window->GetDefaultView());
    window->Clear(sf::Color::White);
    window->Draw(background);
    newGameButton->draw(window);
    optionsButton->draw(window);
    quitButton->draw(window);
}
