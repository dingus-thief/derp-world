#include "Game.h"
#include <sstream>
#include <iostream>
#include "State.h"

Game::Game() : running(true)
{

}

Game::~Game()
{
    //dtor
}

void Game::changeState(State* state)
{

    // cleanup the current state
    if ( !states.empty() )
    {
        states.pop_back();
    }
    // store and init the new state
    states.push_back(state);
}

void Game::pushState(State* state)
{
    // pause current state
    if ( !states.empty() )
    {
        std::cout<<"pushing state\n";
        states.back()->pause();
    }
    // store and init the new state
    states.push_back(state);
    std::cout<<"init new state\n";
}

void Game::popState()
{
    // cleanup the current state
    if ( !states.empty() )
    {
        std::cout<<"popping state\n";
        states.pop_back();
    }

    // resume previous state
    if ( !states.empty() )
    {
        states.back()->resume();
    }
}


void Game::handle()
{
    // let the state handle events
    states.back()->handle();
}

void Game::update()
{
    // let the state update the game
    states.back()->update();
}

void Game::draw()
{
    // let the state draw the screen
    states.back()->render();
}
