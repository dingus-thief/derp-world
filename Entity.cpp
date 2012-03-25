#include "Entity.h"

Entity::Entity(const std::string& name, int health, int damage, int x, int y) : originalX(x), originalY(y), dead(false), attacking(false), speed(0.3), damage(damage), health(health), maxHealth(health), flying(false), isHit(false)
{
    sprite.SetTexture(rm.getImage(name));
    sprite.SetPosition(x, y);
    dir = LEFT;
    previousDir = RIGHT;
    vely = -2;
    rightAttackAnim = thor::FrameAnimation::Create();
    leftAttackAnim = thor::FrameAnimation::Create();
    rightRunAnim = thor::FrameAnimation::Create();
    leftRunAnim = thor::FrameAnimation::Create();
    healthRect.SetSize(sf::Vector2f(40, 10));
    healthRect.SetFillColor(sf::Color::Green);
    maxHealthRect.SetFillColor(sf::Color::Red);
    maxHealthRect.SetSize(sf::Vector2f(40, 10));
    maxHealthRect.SetOutlineThickness(2);
    maxHealthRect.SetOutlineColor(sf::Color::Black);
}

Entity::~Entity()
{
    //dtor
}

void Entity::onHit(unsigned damage, spell spellType)
{
    isHit = true;
    float effectiveness = 0;
    switch(spellType)
    {
        case spell::fire:
            effectiveness = fireEffectiveness;
            break;
        case spell::ice:
            effectiveness = iceEffectiveness;
            break;
        case spell::green:
            effectiveness = energyEffectiveness;
            break;
    }
    health -= damage*effectiveness;
    if(health <= 0)
        dead = true;
}

void Entity::reset()
{
    isHit = false;
    dead = false;
    health = maxHealth;
    sprite.SetPosition(originalX, originalY);
}

void Entity::updateHealthBar()
{
    sf::FloatRect rect1 = sprite.GetGlobalBounds();
    healthRect.SetPosition(rect1.Left - 5, rect1.Top - 15);
    maxHealthRect.SetPosition(rect1.Left - 5, rect1.Top - 15);
    healthRect.SetSize(sf::Vector2f((static_cast<float>(health)/static_cast<float>(maxHealth))*40, 10.f));
}

void Entity::update(const std::vector<Tile>& tiles, const std::list<sf::FloatRect>& flyBlocks)
{
    if(!dead)
    {
        updateHealthBar();
        move(tiles, flyBlocks);
        handleAnimation();
    }
    else
    {
        sprite.Move(0, vely);
        vely += ACCEL;
    }
    return;
}

sf::FloatRect Entity::getBounds()
{
    return sprite.GetGlobalBounds();
}

void Entity::move(const std::vector<Tile>& tiles, const std::list<sf::FloatRect>& flyBlocks)
{
    //out of screen? (=end/start of level)
    sf::FloatRect rect1(sprite.GetGlobalBounds().Left+speed, sprite.GetGlobalBounds().Top, sprite.GetGlobalBounds().Width, sprite.GetGlobalBounds().Height-1);
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
                speed = -speed;
                break;
            }
        }
    }


    if(!flying)
    {
        if(speed > 0) // going right
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
                    willFall = false;
            }
        }
        if(willFall)
            speed = -speed;
    }
    else
    {
        for(auto itr = flyBlocks.begin(); itr != flyBlocks.end(); itr++)
        {
            if(rect1.Intersects(*itr))
                speed = -speed;
        }
    }

    if(speed > 0) dir = RIGHT;
    else dir = LEFT;

    sprite.Move(speed, 0);
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
    if(!dead && isHit)
    {
        window->Draw(maxHealthRect);
        window->Draw(healthRect);
    }
    window->Draw(sprite);
}
