#ifndef NEWGAMESTATE_H
#define NEWGAMESTATE_H
#include "TextEdit.h"
#include "Button.h"
#include "GameState.h"
#include <fstream>


class NewGameState : public State
{
    public:
        NewGameState(sf::RenderWindow* window, StateManager* mgr);
        virtual ~NewGameState();

        void handle();
        void update();
        void render();

        void pause() {};
        void resume() {};

        void init();
        void cleanup();

        static NewGameState* Instance(sf::RenderWindow* window, StateManager* mgr)
       	{
       	    if(newGameState == NULL)
                newGameState = new NewGameState(window, mgr);

            return newGameState;
        }

    private:
        sf::Text nameText;
        TextEdit* nameEdit;
        sf::Text pointsLeftText;
        sf::Text fireSkillText;
        sf::Text iceSkillText;
        sf::Text energySkillText;
        sf::Text firePointsText;
        sf::Text icePointsText;
        sf::Text energyPointsText;
        Button* startButton;
        sf::Sprite background;

        sf::Sprite fireIncrementer;
        sf::Sprite fireDecrementer;
        sf::Sprite iceIncrementer;
        sf::Sprite iceDecrementer;
        sf::Sprite energyIncrementer;
        sf::Sprite energyDecrementer;

        int firePoints;
        int icePoints;
        int energyPoints;

        int pointsLeft;

        void clicked(float x, float y);
        void checkButtons(float x, float y);

        static NewGameState* newGameState;
};

#endif // NEWGAMESTATE_H
