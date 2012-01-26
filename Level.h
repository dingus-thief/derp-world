#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "tinyxml/tinyxml.h"
#include "Entity.h"

class Object{
    public:
        int GetPropertyInt(std::string name);
        float GetPropertyFloat(std::string name);
        std::string GetPropertyString(std::string name);
        std::string name;
        std::string type;
        sf::Rect <int> rect;
        std::map <std::string, std::string> properties;//All properties of the object. Values are stored as strings and mapped by strings(names provided in editor).
};

class Tile;

class Level
{
    public:
        Level(const std::string& filename);
        void draw(sf::RenderWindow* window);
        void update(int frameTime);
        void handle(const sf::Event& event);
        int accumulator;
        virtual ~Level();
        void adjustView(sf::RenderWindow* window, const sf::Sprite& herosprite);
        int width;
        int height;
        std::vector<Entity*> entities;
        std::vector<Tile> tiles;

    private:
        int firstTileID;
        sf::Rect <float> drawingBounds;
        sf::Texture tilesetImage;
        sf::Sprite background;
        //std::vector <sf::Rect <int> > solidObjects;
        //std::vector <Object> objects;
};

#endif // LEVEL_H
