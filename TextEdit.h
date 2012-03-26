#ifndef TEXTEDIT_H
#define TEXTEDIT_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Globals.h"

class TextEdit
{
    public:
        TextEdit(int x, int y, int width);
        ~TextEdit();
        std::string getText();
        void draw(sf::RenderWindow* window);
        void checkClick(float x, float y);
        void handleEvent(const sf::Event& event, sf::RenderWindow* window);
        void handleBackspace();


    private:
        float width;
        bool highlighted;
        bool focused;
        sf::RectangleShape textBox;
        sf::Text text;

};

#endif // TEXTEDIT_H
