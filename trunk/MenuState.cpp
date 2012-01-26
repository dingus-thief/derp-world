#include "MenuState.h"

MenuState::MenuState(sf::RenderWindow* window)
{
    Window = window;
    //background.SetTexture(rm.getImage("menu.png"));
    playButton = new Button("Play", 0, 100);
    optionsButton = new Button("Options", 0, 180);
    quitButton = new Button("Quit", 0, 260);
    matrix.OpenFromFile("Data/Audio/matrixintro.ogg");
    //matrix.Play();
}

void MenuState::update()
{

}

void MenuState::handle()
{
    sf::Event Event;
    while (Window->PollEvent(Event))
    {
        switch (Event.Type)
        {
            case sf::Event::Closed:
                Window->Close();
                break;
            case sf::Event::MouseMoved:
                    checkButtons(Window->ConvertCoords(sf::Mouse::GetPosition(*Window).x, 0).x, Window->ConvertCoords(0, sf::Mouse::GetPosition(*Window).y).y);
                break;
            case sf::Event::MouseButtonPressed:
                if(Event.MouseButton.Button == sf::Mouse::Left)
                    clicked(Window->ConvertCoords(sf::Mouse::GetPosition(*Window).x, 0).x, Window->ConvertCoords(0, sf::Mouse::GetPosition(*Window).y).y);
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
        currentState = 0;
    if(quitButton->isClicked(x, y))
        Window->Close();
}

void MenuState::render()
{
    Window->SetView(Window->GetDefaultView());
    Window->Clear(sf::Color::White);
    //Window->Draw(background);
    playButton->draw(Window);
    optionsButton->draw(Window);
    quitButton->draw(Window);
    Window->Display();
}
