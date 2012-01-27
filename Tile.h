#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

class Tile
{
    public:
        Tile(const sf::Sprite& sprite, bool transparent, bool platform);
        ~Tile();
        void draw(sf::RenderWindow* window);
        sf::Sprite sprite;
        bool transparent;
        bool platform;
        Tile* clone();

    private:

};

#endif // TILE_H
