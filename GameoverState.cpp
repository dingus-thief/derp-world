#include "GameoverState.h"

GameoverState::GameoverState(sf::RenderWindow* window) : window(window)
{
    gameoverText = rm.getText("Game Over", 25);
    setCenter(gameoverText, 200);
    scoreText = rm.getText("Your score: " + to_string(points), 25);
    setCenter(scoreText, 250);
    playAgainButton = new Button("Play again", 0, 360);
    quitButton = new Button("Quit", 0, 440);
}

void GameoverState::run()
{
    while(running)
    {
        handle();
        render();
    }
}

GameoverState::~GameoverState()
{
    delete playAgainButton;
    delete quitButton;
}

void GameoverState::checkButtons(float x, float y)
{
    playAgainButton->checkHL(x, y);
    quitButton->checkHL(x, y);
}

void GameoverState::clicked(float x, float y)
{
    if(playAgainButton->isClicked(x, y))
    {
        running = false;
        currentState = 0;
    }
    if(quitButton->isClicked(x, y))
    {
        running = false;
        currentState = 1;
    }
}

void GameoverState::handle()
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

void GameoverState::render()
{
    window->Clear(sf::Color(0, 0, 0));
    window->Draw(gameoverText);
    window->Draw(scoreText);
    quitButton->draw(window);
    playAgainButton->draw(window);
    window->Display();
}

void GameoverState::update()
{

}


