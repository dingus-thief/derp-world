#include "Hero.h"
#include <iostream>
#define ch 48

Hero::Hero(HUD* hud) : speed(1.7), accumulator(0), dx(0), dy(0), platformSpeed(0, 0), onPlatform(false), dead(false), deathy(0), hud(hud)
{
    load("Data/hero.txt");
    currentSpell = new FireSpell(0, 0, 0);
    oldState.falling = false;
    sprite.SetTexture(rm.getImage("char.png"));
    sprite.SetTextureRect(sf::IntRect(5*42, 0, 42, 42));
    sprite.SetPosition(20, 50);

    initAnimation();
}

void Hero::load(const std::string& filePath)
{
    std::ifstream file(filePath.c_str());

    file >> name;
    file >> fireSkill;
    file >> iceSkill;
    file >> energySkill;
    file >> heroLevel;
    file >> xp;
    file >> lives;
    file >> mana;
    maxMana = mana;
}

void Hero::reset(sf::Vector2f vec)
{
    dy = 0;
    dead = false;
    mana = maxMana;
    sprite.SetPosition(vec);
    currentSpell = new FireSpell(0, 0, 0);
    lives--;
}

int Hero::getLivesLeft()
{
    return lives;
}

void Hero::onDead()
{
    dead = true;
    deathy = -2.5;
}

void Hero::initAnimation()
{
    leftRunAnim = thor::FrameAnimation::Create();
    for(int i = 0; i < 42*5; i += 42)
        leftRunAnim->AddFrame(1.f, sf::IntRect(i, 42, 42, 42));

    rightRunAnim = thor::FrameAnimation::Create();
    for(int i = 0; i < 42*5; i += 42)
        rightRunAnim->AddFrame(1.f, sf::IntRect(i, 0, 42, 42));

    rightJumpAnim = thor::FrameAnimation::Create();
    rightJumpAnim->AddFrame(1.f, sf::IntRect(5*42, 0, 42, 42));

    leftJumpAnim = thor::FrameAnimation::Create();
    leftJumpAnim->AddFrame(1.f, sf::IntRect(5*42, 42, 42, 42));

    leftIdleAnim = thor::FrameAnimation::Create();
    leftIdleAnim->AddFrame(1.f, sf::IntRect(2*42, 42, 42, 42));

    rightIdleAnim = thor::FrameAnimation::Create();
    rightIdleAnim->AddFrame(1.f, sf::IntRect(2*42, 0, 42, 42));

    leftShootAnim = thor::FrameAnimation::Create();
    leftShootAnim->AddFrame(1.f, sf::IntRect(6*42, 42, 42, 42));

    rightShootAnim = thor::FrameAnimation::Create();
    rightShootAnim->AddFrame(1.f, sf::IntRect(6*42, 0, 42, 42));

    animator.AddAnimation("leftRunning", leftRunAnim, sf::Seconds(0.5));
    animator.AddAnimation("rightRunning", rightRunAnim, sf::Seconds(0.5));
    animator.AddAnimation("rightJumping", rightJumpAnim, sf::Seconds(5));
    animator.AddAnimation("leftJumping", leftJumpAnim, sf::Seconds(5));
    animator.AddAnimation("rightIdle", rightIdleAnim, sf::Seconds(5));
    animator.AddAnimation("leftIdle", leftIdleAnim, sf::Seconds(5));
    animator.AddAnimation("leftShoot", leftShootAnim, sf::Seconds(0.5));
    animator.AddAnimation("rightShoot", rightShootAnim, sf::Seconds(0.5));
}

Hero::~Hero()
{
    for(auto itr = spells.begin(); itr != spells.end(); itr++)
    {
        itr = spells.erase(itr);
    }
}

void Hero::shoot()
{
    Spell* newSpell;

    float sign = 0;
    int offset = 0;
    if(oldState.dir == DIR::LEFT)
    {
        sign = -1;
        offset = 0;
        //animator.PlayAnimation("leftShoot");
    }
    else
    {
        sign = 1;
        offset = 42;
        //animator.PlayAnimation("rightShoot");
    }
    if(mana - currentSpell->manacost > 0 && shootClock.GetElapsedTime() > sf::Seconds(0.5))
    {
        shootClock.Restart();
        spells.push_back(currentSpell->clone(sprite.GetGlobalBounds().Left + offset, sprite.GetGlobalBounds().Top+10, sign*1.5));
        mana -= currentSpell->manacost;
    }
}

void Hero::execGravity(Level* level)
{
    if(dy < MAXVEL) //apply acceleration
        dy += ACCEL;
    else dy = MAXVEL;

    //Gravity
    bool fell = false;
    if(!onPlatform)
        if(tryMove(level, 0, 2/3 + dy))
        {
            currState.falling = true;
            fell = true;
        }
    if(!fell)
    {
        if(2/3 + dy > 0) //we were going down
        {
            currState.jumping = false;
            currState.falling = false;
        }
        dy = 0;
    }
}

void Hero::execInput(Level* level)
{

    //KEYBOARD INPUT
    if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Space) && !currState.falling)
    {
        dy = -4.f;
        currState.jumping = true;
    }

    dx = 0;
    currState.idle = false;
    if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
    {
        dx = -0.5;
        tryMove(level, dx*speed, 0);
        currState.dir = DIR::LEFT;
        if(!currState.jumping && !currState.falling)
            currState.walking = true;
    }
    else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
    {
        dx = 0.5;
        tryMove(level, dx*speed, 0);
        currState.dir = DIR::RIGHT;
        if(!currState.jumping && !currState.falling)
            currState.walking = true;
    }
    else
    {
        currState.idle = true;
    }

}

void Hero::update(int frameTime, Level* level)
{
    accumulator += frameTime;
    while(accumulator >= timeStep)
    {
        accumulator -= timeStep;

        if(dead)
        {
            sprite.Move(0, deathy);
            deathy += ACCEL;
            continue;
        }

        checkPlatforms(level->movingTiles); //to see if we need to move with some
        execGravity(level);
        execInput(level);

        for(auto itr = spells.begin(); itr != spells.end(); itr++)
        {
            (*itr)->update();
        }

        regenerateMana();
    }

    //handle animation
    checkItems(level->items);
    handleAnimation(frameTime);
    spellCollisions(level);
    deleteDestroyedSpells();

    hud->setMana(mana);
    hud->setLives(lives);
}

void Hero::regenerateMana()
{
    if(mana < maxMana)
        mana += 0.01;
}

void Hero::checkItems(std::vector<Item>& items)
{
    sf::FloatRect rect = sprite.GetGlobalBounds();
    for(int i = 0; i < items.size(); i++)
    {
        sf::FloatRect rect2 = items[i].getBounds();

        if(rect.Intersects(rect2) && !items[i].isCollected())
        {
            items[i].onCollect();

            switch(items[i].getType())
            {
                case manaPotion:
                {
                    mana += 50;
                    if(mana > maxMana)
                        mana = maxMana;
                } break;
                case healthPotion:
                {
                    lives++;
                }
            }
        }
    }
}

void Hero::checkPlatforms(std::vector<MovingTile> platforms)
{
    onPlatform = false;
    if(!currState.jumping) //don't interfere if we're jumping
    {
        sf::FloatRect rect1 = sprite.GetGlobalBounds();
        rect1.Height = rect1.Height + 1; //for the x-axis platforms we need to increase our height by 1 so we get a collision
        for(int i = 0; i < platforms.size(); i++)
        {
            sf::FloatRect rect2 = platforms[i].getBounds();

            if(rect1.Intersects(rect2))
            {
                if(rect1.Top + rect1.Height + 1 >= rect2.Top) //collision on top
                {
                    onPlatform = true;
                    currState.falling = false; //we landed!
                    sprite.Move(platforms[i].getSpeed()); //move the player along the platform

                    dy = 0; //falling acceleration goes back to zero (landed)
                }
            }
        }
    }
}

void Hero::spellCollisions(Level* level)
{
    for(auto itr = spells.begin(); itr != spells.end(); itr++)
    {
        sf::FloatRect rect = (*itr)->getBounds();
        //tiles
        if(!(*itr)->hit)
        {
            for(int i = 0; i < level->tiles.size(); i++)
            {
                if(!level->tiles[i].transparent)
                {
                    sf::FloatRect rect2 = level->tiles[i].sprite.GetGlobalBounds();
                    if(rect.Intersects(rect2))
                        (*itr)->onHit();
                }
            }
            for(int i = 0; i < level->entities.size(); i++)
            {
                sf::FloatRect rect2 = level->entities[i]->getBounds();
                if(rect.Intersects(rect2) && !level->entities[i]->dead)
                {
                    (*itr)->onHit();
                    level->entities[i]->onHit((*itr)->damage, (*itr)->type());
                    if(level->entities[i]->dead) //they were killed by the spell, add xp
                        hud->addXp(level->entities[i]->getXp());
                }
            }
        }
    }
}

bool Hero::tryMove(Level* level, float x, float y)
{
    bool canMove = true;
    //out of screen? (=end/start of level)
    sf::FloatRect rect1(sprite.GetGlobalBounds().Left+x, sprite.GetGlobalBounds().Top+y, sprite.GetGlobalBounds().Width, sprite.GetGlobalBounds().Height);
    if(rect1.Left < 0 || rect1.Left + rect1.Width > level->width*TILESIZE)
        canMove = false;
    sf::FloatRect intersection;
    //check collision with level->tiles
    for(int j = 0; j < level->tiles.size(); j++)
    {
        if(!level->tiles[j].transparent)
        {
            sf::FloatRect rect2(level->tiles[j].sprite.GetGlobalBounds());

            if(rect1.Intersects(rect2, intersection))
            {
                if(!level->tiles[j].platform)
                {
                    canMove = false;
                }
                else //it's a platform tile
                {
                    if((y > 0 && rect1.Top + rect1.Height - y <= rect2.Top)) //we were going down
                    {
                        canMove = false;
                    }
                }

            }
        }
    }

    for(int i = 0; i < level->movingTiles.size(); i++)
    {
        sf::FloatRect rect2 = level->movingTiles[i].getBounds();

        if(rect1.Intersects(rect2))
        {
            if(y > 0 && rect1.Top + rect1.Height - y <= rect2.Top) //we were going down
            {
                canMove = false;
            }
        }
    }

    for(int i = 0; i < level->entities.size(); i++)
    {
        sf::FloatRect rect2 = level->entities[i]->getBounds();

        if(rect1.Intersects(rect2) && ! level->entities[i]->dead)
        {
            onDead();
            return false;
            canMove = false;
        }
    }

    for(int i = 0; i < level->coins.size(); i++)
    {
        sf::FloatRect rect2 = level->coins[i]->getBounds();

        if(rect1.Intersects(rect2) && ! level->coins[i]->taken)
        {
            level->coins[i]->taken = true;
            level->coins[i]->onHit();
        }
    }

    for(auto itr = level->spikes.begin(); itr != level->spikes.end(); itr++)
    {
        sf::FloatRect rect2 = (*itr).getBounds();

        if(rect1.Intersects(rect2))
        {
            onDead();
            return false;
        }
    }

    if(canMove)
        sprite.Move(x, y);
    return canMove;
}

sf::FloatRect Hero::getBounds()
{
    return sprite.GetGlobalBounds();
}

void Hero::deleteDestroyedSpells()
{
    for(auto itr = spells.begin(); itr != spells.end(); itr++)
    {
        if((*itr)->destroyed)
            itr = spells.erase(itr);
    }
}

void Hero::handle(const sf::Event& event)
{
    switch(event.Type)
    {
        case sf::Event::KeyPressed:
            {
                if(event.Key.Code == sf::Keyboard::Up)
                    shoot();

                if(event.Key.Code == sf::Keyboard::Num1)
                    currentSpell = new FireSpell(0, 0, 0);
                if(event.Key.Code == sf::Keyboard::Num2)
                    currentSpell = new IceSpell(0, 0, 0);
                if(event.Key.Code == sf::Keyboard::Num3)
                    currentSpell = new GreenSpell(0, 0, 0);
                if(event.Key.Code == sf::Keyboard::Num4)
                    currentSpell = new IcicleSpell(0, 0, 0);
                if(event.Key.Code == sf::Keyboard::Num5)
                    currentSpell = new FireBallSpell(0, 0, 0);

                break;
            }
        default:
            break;
    }
}

void Hero::handleAnimation(int frameTime)
{
    if(currState != oldState && !currState.idle)
    {
        animator.StopAnimation();
        if((!currState.falling && !currState.jumping) || onPlatform)
        {
            if(dx < 0)
                animator.PlayAnimation("leftRunning", true);
            else
                animator.PlayAnimation("rightRunning", true);
        }

        else
        {
            if(dx < 0)
                animator.PlayAnimation("leftJumping", true);
            else
                animator.PlayAnimation("rightJumping", true);
        }
        oldState = currState;
    }
    else if(currState != oldState)
    {
        animator.StopAnimation();
        if(oldState.dir == DIR::LEFT)
            animator.PlayAnimation("leftIdle", true);
        else if(oldState.dir == DIR::RIGHT)
            animator.PlayAnimation("rightIdle", true);

        oldState = currState;
    }

    animator.Update(sf::Milliseconds(frameTime));
    animator.Animate(sprite);
}

void Hero::draw(sf::RenderWindow* window)
{
    window->Draw(sprite);

    for(auto itr = spells.begin(); itr != spells.end(); itr++)
    {
        (*itr)->draw(window);
    }
}
