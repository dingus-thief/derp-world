#ifndef HUD_H
#define HUD_H
#include "Globals.h"
#include <thor/Time/StopWatch.hpp>

class HUD
{
    public:
        static HUD* instance();
        ~HUD();
        void update(int lives, int mana);
        void pause();
        void resume();
        void reset();
        void setMaxMana(int maxMana);
        void setMaxLives(int maxLives);
        void draw(sf::RenderWindow* window);
        void addXp(int xp);

    private:
        HUD();
        static HUD* m_instance;
        sf::Text cointext;
        sf::Text timeText;
        sf::Sprite coinSprite;
        sf::RectangleShape manaBar;
        sf::RectangleShape xpBar;
        sf::RectangleShape manaMaxBar;
        sf::RectangleShape xpMaxBar;
        sf::Sprite heart;
        int liveCount;
        sf::RectangleShape spellRect;
        sf::Sprite spellMenu;
        int spellRectX;
        int maxMana;
        int maxLives;
        int maxXp;



        int lastScore;
        int lastTime;
        thor::StopWatch timer;
};

#endif // HUD_H