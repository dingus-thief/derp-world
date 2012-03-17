#include "Hero.h"
#include <iostream>
#define ch 48

const float MAXVEL = 5.0f;
const float ACCEL = 1.f/19.f;

Hero::Hero() : speed(1), accumulator(0), dx(0), dy(0)
{
    oldState.falling = false;
    sprite.SetTexture(rm.getImage("char.png"));
    sprite.SetTextureRect(sf::IntRect(5*42, 0, 42, 42));
    sprite.SetPosition(20, 50);

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

    animator.AddAnimation("leftRunning", leftRunAnim, sf::Seconds(0.5));
    animator.AddAnimation("rightRunning", rightRunAnim, sf::Seconds(0.5));
    animator.AddAnimation("rightJumping", rightJumpAnim, sf::Seconds(5));
    animator.AddAnimation("leftJumping", leftJumpAnim, sf::Seconds(5));
    animator.AddAnimation("rightIdle", rightIdleAnim, sf::Seconds(5));
    animator.AddAnimation("leftIdle", leftIdleAnim, sf::Seconds(5));

}

Hero::~Hero()
{

}

void Hero::reset(Level* level)
{
    level->reset();
    sprite.SetPosition(20, 50);
}


void Hero::shoot()
{
    if(oldState.dir == DIR::LEFT)
        spells.push_back(new FireSpell(sprite.GetGlobalBounds().Left, sprite.GetGlobalBounds().Top+10, -1));
    else
        spells.push_back(new FireSpell(sprite.GetGlobalBounds().Left + 32, sprite.GetGlobalBounds().Top+10, 1));
}

void Hero::update(int frameTime, Level* level)
{
    accumulator += frameTime;
    while(accumulator >= timeStep)
    {
        if(dy < MAXVEL) //apply acceleration
            dy += ACCEL;
        else dy = MAXVEL;

        //Gravity
        if(tryMove(level, 0, 2/3 + dy))
            currState.falling = true;
        else
        {
            if(2/3 + dy > 0) //we were going down
            {
                currState.jumping = false;
                currState.falling = false;
            }
            dy = 0;
        }

        //Sprinting
        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::LShift))
            speed = 1.7;
        else
            speed = 1.3;


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
        else currState.idle = true;

        for(auto itr = spells.begin(); itr != spells.end(); itr++)
        {
            (*itr)->update();
        }

        accumulator -= timeStep;
    }

    //handle animation
    handleAnimation(frameTime);
    spellCollisions(level);
    deleteDestroyedSpells();
}

void Hero::spellCollisions(Level* level)
{
    for(auto itr = spells.begin(); itr != spells.end(); itr++)
    {
        sf::FloatRect rect = (*itr)->getBounds();
        //tiles
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
                level->entities[i]->kill();
            }
        }
    }
}

bool Hero::tryMove(Level* level, float x, float y)
{
    //out of screen? (=end/start of level)
    sf::FloatRect rect1(sprite.GetGlobalBounds().Left+x, sprite.GetGlobalBounds().Top+y, sprite.GetGlobalBounds().Width, sprite.GetGlobalBounds().Height);
    if(rect1.Left < 0 || rect1.Left + rect1.Width > level->width*TILESIZE)
        return false;
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
                    return false;
                }
                else //it's a platform tile
                {
                    if((y > 0 && rect1.Top + rect1.Height - y <= rect2.Top)) //we were going down
                    {
                        return false;
                    }
                }

            }
        }
    }
    for(int i = 0; i < level->entities.size(); i++)
    {
        sf::FloatRect rect2 = level->entities[i]->getBounds();

        if(rect1.Intersects(rect2) && ! level->entities[i]->dead)
        {
            reset(level);
            gameover = true;
            return false;
        }
    }
    sprite.Move(x, y);
    return true;
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
        if(event.Key.Code == sf::Keyboard::Space)
        {

        }
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
        if(!currState.falling && !currState.jumping)
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
