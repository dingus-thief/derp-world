#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>

class Tile
{
public:
    Tile(const sf::Sprite& sprite, bool transparent, bool platform, bool kill);
    ~Tile();
    void draw(sf::RenderWindow* window);
    sf::Vector2f getCenterPoint();
    sf::FloatRect getBounds();
    sf::Sprite sprite;
    bool transparent;
    bool platform;
    bool kill;
    Tile* clone();

private:

};

#endif // TILE_H
