#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "tinyxml/tinyxml.h"
#include "Entity.h"
#include "Cannon.h"

class Tile;

class Level
{
    public:
        Level(const std::string& filename);
        void draw(sf::RenderWindow* window);
        void update(int frameTime);
        void handle(const sf::Event& event);
        void reset();

        virtual ~Level();
        void adjustView(sf::RenderWindow* window, const sf::Sprite& herosprite);
        int width;
        int height;
        std::vector<Object*> objects;
        std::vector<Entity*> entities;
        std::vector<Tile> tiles;

    private:
        int accumulator;
        int firstTileID;
        sf::Rect <float> drawingBounds;
        sf::Texture tilesetImage;
        sf::Sprite background;
        //std::vector <sf::Rect <int> > transparentObjects;
        //std::vector <Object> objects;
};

#endif // LEVEL_H
