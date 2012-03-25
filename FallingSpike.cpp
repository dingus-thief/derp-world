#include "FallingSpike.h"

FallingSpike::FallingSpike(int x, int y) : falling(false), dead(false), vely(0), originalPos(x, y)
{
    sprite.SetTexture(rm.getImage("iceSpike.png"));
    sprite.SetPosition(x, y);
}

FallingSpike::~FallingSpike()
{
    //dtor
}

void FallingSpike::update(sf::FloatRect heroRect, std::vector<Tile> tiles)
{
    sf::FloatRect rect1 = sprite.GetGlobalBounds();
    for(unsigned i = 0; i < tiles.size(); i++)
        if(rect1.Intersects(tiles[i].getBounds()))
            onHit();

    rect1 = sf::FloatRect(rect1.Left, rect1.Top, rect1.Width, rect1.Height + 200);
    if(rect1.Intersects(heroRect))
        falling = true;

    if(falling)
    {
        sprite.Move(0, vely);
        vely += 2*ACCEL/3;
    }
}

void FallingSpike::reset()
{
    vely = 0;
    dead = 0;
    falling = false;
    sprite.SetPosition(originalPos);
}

void FallingSpike::draw(sf::RenderWindow* window)
{
    if(!dead)
        window->Draw(sprite);
}

void FallingSpike::onHit()
{
    dead = true;
}

sf::FloatRect FallingSpike::getBounds()
{
    return sprite.GetGlobalBounds();
}
