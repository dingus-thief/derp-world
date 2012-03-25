#ifndef STATEMANAGER_H
#define STATEMANAGER_H
#include <vector>
#include <SFML/Graphics.hpp>


    class State;

    class StateManager
    {
        public:
            StateManager();
            ~StateManager();

            void draw();
            void handle();
            void update();

            void changeState(State* state);
            void pushState(State* state);
            void popState();

            bool running;

        private:
            std::vector<State*> states;

    };

#endif // STATEMANAGER_H
