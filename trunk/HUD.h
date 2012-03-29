#ifndef HUD_H
#define HUD_H
#include "Globals.h"
#include <thor/Time/StopWatch.hpp>

class HUD
{
    public:
        HUD();
        ~HUD();
        void update();
        void pause();
        void resume();
        void reset();
        void setMaxMana(int maxMana);
        void setLives(int mLives);
        void setMaxXp(int mxp);
        void setMana(int mMana);
        void draw(sf::RenderWindow* window);
        void addXp(int xp);

    private:
        sf::Text cointext;
        sf::Text timeText;
        sf::Sprite coinSprite;
        sf::RectangleShape manaBar;
        sf::RectangleShape xpBar;
        sf::RectangleShape manaMaxBar;
        sf::RectangleShape xpMaxBar;
        sf::Sprite heart;
        sf::RectangleShape spellRect;
        sf::Sprite spellMenu;
        int spellRectX;
        int maxMana;
        int maxXp;
        int liveCount;

        int lastScore;
        int lastTime;
        thor::StopWatch timer;
};

#endif // HUD_H
