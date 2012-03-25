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

        sf::FloatRect getBounds();
        void draw(sf::RenderWindow* window);

    private:
        sf::Sprite sprite;
        bool falling;
        bool dead;
        float vely;
};

#endif // FALLINGSPIKE_H
