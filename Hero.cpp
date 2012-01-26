#include "Hero.h"
#include <iostream>
#define ch 16

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

void Hero::update(int frameTime, Level* level)
{
    accumulator += frameTime;
    while(accumulator >= timeStep)
    {
        if(vely < 4.f) //apply acceleration
            vely += 1.f/19.f;
        else vely = 4.f;

        if(level->tryMove(sprite, 0, 2/3 + vely))//always apply gravity
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
        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::LShift))
            speed = 1.5;
        else
            speed = 1.0;
        if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Space) && !falling)
        {
            vely = -3.f;
            jumping = true;
        }
        dir = DIR::IDLE;
        if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Left))
        {
            level->tryMove(sprite, -0.5*speed, 0);
            dir = DIR::LEFT;
            if(!jumping && !falling)
                walking = true;
        }
        else if (sf::Keyboard::IsKeyPressed(sf::Keyboard::Right))
        {
            level->tryMove(sprite, 0.5*speed, 0);
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
