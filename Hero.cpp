#include "Hero.h"
#include <iostream>
#define ch 16

const float MAXVEL = 4.0f;
const float ACCEL = 1.f/19.f;

Hero::Hero() : vely(0), falling(true),  speed(1),  dir(DIR::IDLE), walking(false)
{
    sprite.SetTexture(rm.getImage("char.png"));
    sprite.SetTextureRect(sf::IntRect(0, 0, 14, ch));
    sprite.SetPosition(20, 50);
}

Hero::~Hero()
{
    //dtor
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
        if(level->tiles[j].solid)
        {
            sf::FloatRect rect2(level->tiles[j].sprite.GetGlobalBounds());
            if(rect1.Intersects(rect2, intersection))
            {
                if(!level->tiles[j].jumpThrough)
                {
                    return false;
                }
                else //it's a jumpthrough tile
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
        sf::FloatRect rect2 = level->entities[i]->sprite.GetGlobalBounds();
        if(rect1.Intersects(rect2) && ! level->entities[i]->dead)
        {
            if(rect1.Top + rect1.Height - y < rect2.Top) //we were going down
            {
                level->entities[i]->kill();
                vely = -1.5;
            }
            //else we're dead
        }
    }
    sprite.Move(x, y);
    return true;
}

void Hero::update(int frameTime, Level* level)
{
    accumulator += frameTime;
    while(accumulator >= timeStep)
    {
        if(vely < MAXVEL) //apply acceleration
            vely += ACCEL;
        else vely = MAXVEL;

        //Gravity
        if(tryMove(level, 0, 2/3 + vely))
            falling = true;
        else
        {
            if(2/3 + vely > 0) //we were going down
            {
                jumping = false;
                falling = false;
            }
            vely = 0;
        }

        //Sprinting
        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::LShift))
            speed = 1.5;
        else
            speed = 1.0;


        //KEYBOARD INPUT
        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Space) && !falling)
        {
            vely = -3.f;
            jumping = true;
        }
        dir = DIR::IDLE;
        if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
        {
            tryMove(level, -0.5*speed, 0);
            dir = DIR::LEFT;
            if(!jumping && !falling)
                walking = true;
        }
        else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
        {
            tryMove(level, 0.5*speed, 0);
            dir = DIR::RIGHT;
            if(!jumping && !falling)
                walking = true;
        }
        accumulator -= timeStep;
    }

    //handle animation
    handleAnimation(frameTime);
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
    }
}

void Hero::handleAnimation(int frameTime)
{
    aniAccu += frameTime;
    if(dir != DIR::IDLE)
        previousDir = dir;
    int y = 0;
    if(previousDir == DIR::LEFT)
    {
        y = ch+1;
    }
    if(jumping || falling)
    {
        sprite.SetTextureRect(sf::IntRect(29, y, 14, ch));
    }
    else if(dir != DIR::IDLE)
    {
        if(aniAccu < 150/speed)
            sprite.SetTextureRect(sf::IntRect(0, y, 14, ch));
        else if(aniAccu < 300/speed)
        {
            sprite.SetTextureRect(sf::IntRect(15, y, 14, ch));
        }
        else
            aniAccu -= 300/speed;
    }
    else //idle
    {
        sprite.SetTextureRect(sf::IntRect(0, y, 14, ch));
    }
}

void Hero::draw(sf::RenderWindow* window)
{
    window->Draw(sprite);
}
