#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics.hpp>

class Object
{
    public:
        Object(const sf::Sprite& sprite);
        ~Object();

        void draw(sf::RenderWindow* window);
        virtual void update() = 0;

    protected:
        sf::Sprite sprite;

};

#endif // OBJECT_H
