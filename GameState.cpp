#include "GameState.h"
#include <iostream>

GameState* GameState::gameState = 0;

GameState::GameState(sf::RenderWindow* window, StateManager* mgr) : State(window, mgr)
{
    loadingSprite.SetTexture(rm.getImage("loading.png"));
}

void GameState::init()
{
    window->Clear();
    window->Draw(loadingSprite);
    window->Display();
    sf::Vector2f center(WIDTH/2, HEIGHT/2);
    sf::Vector2f halfsize(WIDTH, HEIGHT);
    sf::View view_(center, halfsize);
    view = view_;
    hud = new HUD;
    hero = new Hero(hud);
    level = new Level(levelPath);
    music = new sf::Music;
    music->OpenFromFile("Data/Audio/background.ogg");
    music->SetLoop(true);
    //music->Play();
}

GameState::~GameState()
{

}

void GameState::cleanup()
{
    delete hero;
    delete level;
    delete hud;
    delete music;
}

void GameState::update()
{
    int frameTime = Clock.GetElapsedTime().AsMilliseconds();
    Clock.Reset(true);


    level->update(frameTime, hero->getBounds());
    hero->update(frameTime, level);
    hud->update();

    level->adjustView(window, hero->sprite);

    if(hero->getBounds().Top > level->height*TILESIZE) //player died
    {
        hero->reset(level->getLastCheckpoint());
        level->reset();
        stateManager->pushState(LiveLostState::Instance(window, stateManager, hero->getLivesLeft()));
    }

    /*if(gameover)
    {
        gameover = false;
        std::cout<<"gameover\n";
        stateManager->pushState(GameoverState::Instance(window, stateManager));
    }*/
}

void GameState::resume()
{
    hud->resume();
    sf::View view(sf::Vector2f(WIDTH/2, HEIGHT/2), sf::Vector2f(WIDTH, HEIGHT));
    window->SetView(view);
    Clock.Start();
}

void GameState::pause()
{
    hud->pause();
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
                        stateManager->popState();
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
    level->draw(window);
    hero->draw(window);
    hud->draw(window);
}
