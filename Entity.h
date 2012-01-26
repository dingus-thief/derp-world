#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Tile.h"

class Entity
{
    public:
        Entity(const std::string& name, int x, int y);
        ~Entity();
        void update(const std::vector<Tile>& tiles);
        void draw(sf::RenderWindow* window);
        sf::Sprite sprite;

    private:
        DIR previousDir;
        int accumulator;
        int aniAccu;
        float speed;
        float vely;
        DIR dir;


};

#endif // ENTITY_H
