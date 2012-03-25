#include "LiveLostState.h"

LiveLostState* LiveLostState::liveLostState = NULL;

LiveLostState::LiveLostState(sf::RenderWindow* window, StateManager* mgr) : State(window, mgr), goingDown(true), pixelsGoneDown(0)
{
    background.SetTexture(rm.getImage("liveLostBackground.png"));
    drawOnTop = true;
}

void LiveLostState::checkButtons(float x, float y)
{
    restartButton->checkHL(x, y);;
}

void LiveLostState::clicked(float x, float y)
{
    if(restartButton->isClicked(x, y))
        stateManager->popState();
}

void LiveLostState::handle()
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

void LiveLostState::update()
{
    if(goingDown)
    {
        background.Move(0, 3);
        text.Move(0, 3);
        restartButton->move(0, 3);


        pixelsGoneDown += 3;
        if(pixelsGoneDown > 300)
            goingDown = false;
    }
}

void LiveLostState::render()
{
    window->Draw(background);
    window->Draw(text);
    restartButton->draw(window);
}

void LiveLostState::pause() {}

void LiveLostState::resume() {}

void LiveLostState::init()
{
    text = rm.getText("You died!\nYou have " + to_string(livesLeft) + " lifes left.");
    background.SetPosition(window->ConvertCoords(100, -200));
    restartButton = new Button("Continue", 0, static_cast<int>(window->ConvertCoords(0, -50).y));
    restartButton->setPosition(static_cast<int>(window->ConvertCoords(200, -50).x), static_cast<int>(window->ConvertCoords(200, -50).y));
    text.SetPosition(static_cast<int>(window->ConvertCoords(200, -100).x), static_cast<int>(window->ConvertCoords(200, -100).y));
}

void LiveLostState::cleanup()
{
    goingDown = true;
    pixelsGoneDown = 0;
    delete restartButton;
}
