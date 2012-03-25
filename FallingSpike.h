#ifndef FALLINGSPIKE_H
#define FALLINGSPIKE_H
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Globals.h"
#include "Constants.h"

class FallingSpike
{
    public:
        FallingSpike(int x, int y);
        virtual ~FallingSpike();
        void update(sf::FloatRect heroRect, std::vector<Tile> tiles);
        void onHit();
        void reset();

        sf::FloatRect getBounds();
        void draw(sf::RenderWindow* window);

    private:
        sf::Sprite sprite;
        bool falling;
        bool dead;
        float vely;
        sf::Vector2f originalPos;
};

#endif // FALLINGSPIKE_H
