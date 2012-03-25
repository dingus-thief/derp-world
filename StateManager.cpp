#include "StateManager.h"
#include "State.h"


    StateManager::StateManager()
    {
        //ctor
    }

    StateManager::~StateManager()
    {
        states.clear();
    }

    void StateManager::changeState(State* state)
    {
        // cleanup the current state
        /*if ( !states.empty() ) {
            states.back()->cleanup();
            states.pop_back();
        }*/

        // store and init the new state
        states.push_back(state);
        states.back()->init();
    }

    void StateManager::pushState(State* state)
    {
        // pause current state
        if ( !states.empty() ) {
            states.back()->pause();
        }

        // store and init the new state
        states.push_back(state);
        states.back()->init();
    }

    void StateManager::popState()
    {
        // cleanup the current state
        if ( !states.empty() ) {
            states.back()->cleanup();
            states.pop_back();
        }

        // resume previous state
        if ( !states.empty() ) {
            states.back()->resume();
        }
        else running = false;
    }


    void StateManager::handle()
    {
        if(!states.empty())
            states.back()->handle();
    }

    void StateManager::update()
    {
        if(!states.empty())
            states.back()->update();
    }

    void StateManager::draw()
    {
        if(!states.empty())
        {
            if(states.back()->drawOnTop)
                states[states.size()-2]->render();
            states.back()->render();
        }
    }

