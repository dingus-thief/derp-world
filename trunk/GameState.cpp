#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) : Window(window)
{
    sf::Vector2f center(WIDTH/2, HEIGHT/2);
    sf::Vector2f halfsize(WIDTH, HEIGHT);
    sf::View view_(center, halfsize);
    view = view_;
    hero = new Hero;
    level = new Level("map4.tmx");
    currentLvl = 0;
}


void GameState::update()
{
    hero->update(Window->GetFrameTime(), level);
    level->update(Window->GetFrameTime());
}

void GameState::reset()
{

}

void GameState::updateText()
{
    scoreText.SetString("Score: " + to_string(points));
}

void GameState::handle()
{
    sf::Event Event;
    while (Window->PollEvent(Event))
    {
        level->handle(Event);
        switch (Event.Type)
        {
        case sf::Event::Closed:
            Window->Close();
            break;
        case sf::Event::KeyPressed:
        {
            if(Event.Key.Code == sf::Keyboard::P)
            {

            }
            if(Event.Key.Code == sf::Keyboard::Escape)
            {
                currentState = 1;
            }
        }
        case sf::Event::MouseButtonPressed:
        {
            if(Event.MouseButton.Button == sf::Mouse::Left)
                break;
        }
        default:
            break;
        }
    }
}

void GameState::render()
{
    Window->Clear(sf::Color(100, 100, 240));
    level->adjustView(Window, hero->sprite);
    level->draw(Window);
    hero->draw(Window);
    Window->Display();
}
