#include "MenuState.h"


MenuState::MenuState(sf::RenderWindow* window, Game* game) : State(game, window)
{
    background.SetTexture(rm.getImage("menuBackground.png"));
    playButton = new Button("Play", 0, 50);
    optionsButton = new Button("Options", 0, 110);
    quitButton = new Button("Quit", 0, 170);
    matrix.OpenFromFile("Data/Audio/matrixintro.ogg");
    //matrix.Play();
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
            default: break;
        }
    }
}

void MenuState::checkButtons(float x, float y)
{
    playButton->checkHL(x, y);
    optionsButton->checkHL(x, y);
    quitButton->checkHL(x, y);
}

void MenuState::clicked(float x, float y)
{
    if(playButton->isClicked(x, y))
        game->pushState(new GameState(window, game));
    if(quitButton->isClicked(x, y))
        window->Close();
}

void MenuState::render()
{
    window->SetView(window->GetDefaultView());
    window->Clear(sf::Color::White);
    window->Draw(background);
    playButton->draw(window);
    optionsButton->draw(window);
    quitButton->draw(window);
    window->Display();
}
