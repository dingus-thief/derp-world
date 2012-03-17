#include "Globals.h"
#include <sstream>
#include <iostream>

ResourceManager rm;
SoundManager sm;
thor::FrameAnimation::Ptr explosion(new thor::FrameAnimation);
thor::StopWatch Clock;


//std::mt19937 rng;

int points = 0;
int lives = 3;
int currentState = 1;

bool gameover = false;
bool dead = false;
bool Pause = false;

std::string to_string(int number)
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}
void setCenter(sf::Text& txt, int y)
{
    sf::FloatRect rect = txt.GetGlobalBounds();
    txt.SetPosition((WIDTH)/2 - rect.Width/2 , y);
}

float abso(float i)
{
    if(i < 0)
    return -i;
    else
    return i;
}
