#ifndef BUTTON_H
#define BUTTON_H
#include <string>
#include "Globals.h"

class Button
{
    public:
        Button(const std::string& txt, int x, int y);
        void draw(sf::RenderWindow* Window);
        bool isClicked(float x, float y);
        void checkHL(float x, float y);
        void setPosition(int mx, int my);
        void centerText();
        void center(int start, int end);
        void move(int mx, int my);
        bool highlighted;

    private:
        sf::Sprite buttonSprite;
        sf::Text* text;
        int x;
        int y;


};

#endif // BUTTON_H
