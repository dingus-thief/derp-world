#ifndef HERO_H
#define HERO_H
#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>
#include "Globals.h"
#include "Level.h"
#include <Thor/Time/Timer.hpp>

class Hero
{
    public:
        Hero();
        ~Hero();
        void draw(sf::RenderWindow* window);
        void update(int frameTime, Level* level);
        void handle(const sf::Event& event);
        sf::Sprite sprite;
        bool jumping;
        bool falling;
        bool walking;
        int aniAccu;
        int accumulator;
        DIR dir;
        DIR previousDir;
        float vely;
        float speed;

    private:
        void handleAnimation(int frameTime);

};

#endif // HERO_H
