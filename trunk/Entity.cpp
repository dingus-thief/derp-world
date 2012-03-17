#include "Entity.h"

Entity::Entity(const std::string& name, int health, int damage, int x, int y) : dead(false), x(0.3), damage(damage), health(health)
{
    sprite.SetTexture(rm.getImage(name));
    sprite.SetPosition(x, y);
    dir = LEFT;
    previousDir = RIGHT;
    vely = 5;
    rightAttackAnim = thor::FrameAnimation::Create();
    leftAttackAnim = thor::FrameAnimation::Create();
    rightRunAnim = thor::FrameAnimation::Create();
    leftRunAnim = thor::FrameAnimation::Create();
}

Entity::~Entity()
{
    //dtor
}

void Entity::kill()
{
    dead = true;
}

void Entity::update(const std::vector<Tile>& tiles)
{
    move(tiles);
    handleAnimation();
    return;
}

sf::FloatRect Entity::getBounds()
{
    return sprite.GetGlobalBounds();
}

void Entity::move(const std::vector<Tile>& tiles)
{
    //out of screen? (=end/start of level)
    sf::FloatRect rect1(sprite.GetGlobalBounds().Left+x, sprite.GetGlobalBounds().Top, sprite.GetGlobalBounds().Width, sprite.GetGlobalBounds().Height-1);
    sf::FloatRect intersection;

    dir  = previousDir;

    //check collision with tiles
    for(unsigned j = 0; j < tiles.size(); j++) // check for the sides
    {
        if(!tiles[j].transparent)
        {
            sf::FloatRect rect2(tiles[j].sprite.GetGlobalBounds());
            if(rect1.Intersects(rect2, intersection))
            {
                x = -x;
                if(x > 0) dir = RIGHT;
                else dir = LEFT;
                break;
            }
        }
    }
    if(x > 0) // going right
        rect1 = sf::FloatRect(sprite.GetGlobalBounds().Left + TILESIZE, sprite.GetGlobalBounds().Top+2, sprite.GetGlobalBounds().Width-2, sprite.GetGlobalBounds().Height);
    else //going left
        rect1 = sf::FloatRect(sprite.GetGlobalBounds().Left - TILESIZE, sprite.GetGlobalBounds().Top+2, sprite.GetGlobalBounds().Width-2, sprite.GetGlobalBounds().Height);
    bool willFall = true;
    for(unsigned j = 0; j < tiles.size(); j++) // check for the sides
    {
        if(!tiles[j].transparent)
        {
            sf::FloatRect rect2(tiles[j].sprite.GetGlobalBounds());
            if(rect1.Intersects(rect2, intersection))
            {
                willFall = false;
            }
        }
    }
    if(willFall)
    {
        x = -x;
        if(x > 0) dir = RIGHT;
        else dir = LEFT;
    }

    sprite.Move(x, 0);
}

void Entity::handleAnimation()
{
    if(dir != previousDir)
    {
        animator.StopAnimation();
        if(dir == DIR::LEFT)
        {
            animator.PlayAnimation("leftRunning", true);
        }
        else
            animator.PlayAnimation("rightRunning", true);

    }
    previousDir = dir;

    animator.Update(sf::Milliseconds(timeStep));
    animator.Animate(sprite);
}

void Entity::draw(sf::RenderWindow* window)
{
    if(!dead)
        window->Draw(sprite);
}
