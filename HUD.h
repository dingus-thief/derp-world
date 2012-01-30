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
        void draw(sf::RenderWindow* window, const sf::FloatRect& rect);

    private:
        sf::Text cointext;
        sf::Text timeText;
        sf::Sprite coinSprite;
        int lastScore;
        int lastTime;
        thor::StopWatch timer;
};

#endif // HUD_H
