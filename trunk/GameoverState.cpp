#include "GameoverState.h"

GameoverState::GameoverState(sf::RenderWindow* window, Game* game) : State(game, window)
{
    gameoverText = rm.getText("Game Over", 20);
    setCenter(gameoverText, 60);
    scoreText = rm.getText("Your score: " + to_string(points), 20);
    setCenter(scoreText, 100);
    playAgainButton = new Button("Play again", 0, 150);
    quitButton = new Button("Quit", 0, 210);
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
        game->popState();
    }
    if(quitButton->isClicked(x, y))
    {

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
    window->SetView(window->GetDefaultView());
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


