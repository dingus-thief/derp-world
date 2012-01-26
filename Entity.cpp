#include "Entity.h"

Entity::Entity(const sf::Sprite& sprite) : sprite(sprite), x(0.3)
{
    dir = LEFT;
    previousDir = LEFT;
    vely = 5;
}

Entity::~Entity()
{
    //dtor
}

void Entity::update(const std::vector<Tile>& tiles)
{
    //out of screen? (=end/start of level)
    sf::FloatRect rect1(sprite.GetGlobalBounds().Left+x, sprite.GetGlobalBounds().Top, sprite.GetGlobalBounds().Width, sprite.GetGlobalBounds().Height);
    sf::FloatRect intersection;
    //check collision with tiles
    for(int j = 0; j < tiles.size(); j++) // check for the sides
    {
        if(tiles[j].solid)
        {
            sf::FloatRect rect2(tiles[j].sprite.GetGlobalBounds());
            if(rect1.Intersects(rect2, intersection))
            {
                x = -x;
                break;
            }
        }
    }
    if(x > 0) // going right
        rect1 = sf::FloatRect(sprite.GetGlobalBounds().Left + 16, sprite.GetGlobalBounds().Top+2, sprite.GetGlobalBounds().Width, sprite.GetGlobalBounds().Height);
    else //going left
        rect1 = sf::FloatRect(sprite.GetGlobalBounds().Left - 16, sprite.GetGlobalBounds().Top+2, sprite.GetGlobalBounds().Width, sprite.GetGlobalBounds().Height);
    bool willFall = true;
    for(int j = 0; j < tiles.size(); j++) // check for the sides
    {
        if(tiles[j].solid)
        {
            sf::FloatRect rect2(tiles[j].sprite.GetGlobalBounds());
            if(rect1.Intersects(rect2, intersection))
            {
                willFall = false;
            }
        }
    }
    if(willFall)
        x = -x;

    sprite.Move(x, 0);
    return;
}

void Entity::draw(sf::RenderWindow* window)
{
    window->Draw(sprite);
}
