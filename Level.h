#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "tinyxml/tinyxml.h"
#include "Entity.h"
#include "Cannon.h"
#include "Bullet.h"
#include "Coin.h"
#include "HUD.h"

class Tile;

class Level
{
    friend class Hero;

    public:
        Level(const std::string& filename);
        void draw(sf::RenderWindow* window);
        void update(int frameTime);
        void handle(const sf::Event& event);
        void reset();

        virtual ~Level();
        void adjustView(sf::RenderWindow* window, const sf::Sprite& herosprite);


    private:
        HUD hud;
        int accumulator;
        int firstTileID;
        sf::Rect <float> drawingBounds;
        sf::Texture tilesetImage;
        sf::Sprite background;
        int width;
        int height;
        std::vector<Cannon*> cannons;
        std::vector<Entity*> entities;
        std::list<Bullet*> bullets;
        std::vector<Coin*> coins;
        std::vector<Tile> tiles;
        //std::vector <sf::Rect <int> > transparentObjects;
        //std::vector <Object> objects;
};

#endif // LEVEL_H
