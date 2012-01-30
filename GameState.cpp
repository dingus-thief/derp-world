#include "GameState.h"
#include <iostream>


GameState::GameState(sf::RenderWindow* window, Game* game) : State(game, window)
{
    sf::Vector2f center(WIDTH/2, HEIGHT/2);
    sf::Vector2f halfsize(WIDTH, HEIGHT);
    sf::View view_(center, halfsize);
    view = view_;
    hero = new Hero;
    level = new Level("Data/Levels/demo.tmx");
    std::cout<<"constructor GameState finished";
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
    hero->update(frameTime, level);
    level->update(frameTime);
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
    level->hud.resume();
    Clock.Start();
}

void GameState::pause()
{
    level->hud.pause();
    Clock.Stop();
}

void GameState::handle()
{
    std::cout<<"handle\n";

    sf::Event Event;
    while (window->PollEvent(Event))
    {
        level->handle(Event);
        switch (Event.Type)
        {
        case sf::Event::Closed:
            window->Close();
            break;
        case sf::Event::KeyPressed:
        {
            if(Event.Key.Code == sf::Keyboard::P)
            {

            }
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
    std::cout<<"render\n";
    window->Clear(sf::Color(100, 100, 240));
    level->adjustView(window, hero->sprite);
    level->draw(window);
    hero->draw(window);
    window->Display();
}
