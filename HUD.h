#ifndef HUD_H
#define HUD_H
#include "Globals.h"
#include <thor/Time/StopWatch.hpp>

class HUD
{
    public:
        static HUD* instance();
        ~HUD();
        void update(int health, int mana);
        void pause();
        void resume();
        void reset();
        void setMaxMana(int maxMana);
        void setMaxHealth(int maxHealth);
        void draw(sf::RenderWindow* window);

    private:
        HUD();
        static HUD* m_instance;
        sf::Text cointext;
        sf::Text timeText;
        sf::Sprite coinSprite;
        sf::RectangleShape manaBar;
        sf::RectangleShape manaMaxBar;
        sf::RectangleShape healthMaxBar;
        sf::RectangleShape healthBar;
        sf::RectangleShape spellRect;
        sf::Sprite spellMenu;
        int spellRectX;
        int maxMana;
        int maxHealth;

        int lastScore;
        int lastTime;
        thor::StopWatch timer;
};

#endif // HUD_H
