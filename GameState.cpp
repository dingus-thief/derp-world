#include "GameState.h"
#include <iostream>


GameState::GameState(sf::RenderWindow* window, Game* game) : State(game, window)
{
    sf::Vector2f center(WIDTH/2, HEIGHT/2);
    sf::Vector2f halfsize(WIDTH, HEIGHT);
    sf::View view_(center, halfsize);
    view = view_;
    hero = new Hero;
    level = new Level("Data/Levels/coolio.tmx");
}

GameState::~GameState()
{
    //level->reset();
    delete hero;
    delete level;
}


void GameState::update()
{
    int frameTime = Clock.GetElapsedTime().AsMilliseconds();
    Clock.Reset(true);

    level->update(frameTime);
    hero->update(frameTime, level);
    if(gameover)
    {
        gameover = false;
        std::cout<<"gameover\n";
        game->pushState(new GameoverState(window, game));
    }
}

void GameState::init()
{

}

void GameState::cleanup()
{

}

void GameState::resume()
{
    HUD::instance()->resume();
    Clock.Start();
}

void GameState::pause()
{
    HUD::instance()->pause();
    Clock.Stop();
}

void GameState::handle()
{
    sf::Event Event;
    while (window->PollEvent(Event))
    {
        level->handle(Event);
        hero->handle(Event);
        switch (Event.Type)
        {
        case sf::Event::Closed:
            window->Close();
            break;
        case sf::Event::KeyPressed:
        {
            if(Event.Key.Code == sf::Keyboard::Escape)
            {
                game->popState();
                return;
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
    window->Clear(sf::Color(100, 100, 240));
    level->adjustView(window, hero->sprite);
    level->draw(window);
    hero->draw(window);
    HUD::instance()->draw(window);
    window->Display();
}
