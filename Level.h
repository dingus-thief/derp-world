#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "tinyxml/tinyxml.h"
#include "Skeleton.h"
#include "Bat.h"
#include "Snake.h"
#include "Cannon.h"
#include "MovingTile.h"
#include "Bullet.h"
#include "Coin.h"
#include "HUD.h"
#include "FallingSpike.h"

class Tile;

class Level
{
        friend class Hero;
        friend class GameState;

    public:
        Level(const std::string& filename);
        void draw(sf::RenderWindow* window);
        void update(int frameTime, sf::FloatRect heroRect);
        void handle(const sf::Event& event);
        void reset();
        sf::Vector2f getLastCheckpoint();

        ~Level();
        void adjustView(sf::RenderWindow* window, const sf::Sprite& herosprite);


    private:
        void shoot();

        int accumulator;
        int firstTileID;
        sf::Rect <float> drawingBounds;
        sf::Texture tilesetImage;
        sf::Sprite background;
        int width;
        int height;
        std::vector<Entity*> entities;
        std::list<sf::FloatRect> flyBlocks;
        std::list<sf::FloatRect> platformBlocks;
        std::vector<Coin*> coins;
        std::vector<FallingSpike> spikes;
        std::vector<Tile> tiles;
        std::vector<MovingTile> movingTiles;
        sf::Vector2f lastCheckpoint;
        //std::vector <sf::Rect <int> > transparentObjects;
        //std::vector <Object> objects;
};

#endif // LEVEL_H
