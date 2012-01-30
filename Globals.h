#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include "ResourceManager.h"
#include "SoundManager.h"
#include <SFML/Audio.hpp>
#include <Thor/Animation/FrameAnimation.hpp>
#include <Thor/Time/StopWatch.hpp>
#include <random>

const int WIDTH = 400;
const int HEIGHT = 300;
const int TILESIZE = 16;
const int timeStep = 5;

//extern std::mt19937 rng;

extern thor::StopWatch Clock;

extern int points;
extern int lives;
extern int currentState;

extern bool gameover;
extern bool dead;
extern bool Pause;
extern bool colliding[4];

enum DIR{LEFT, RIGHT, IDLE};

extern class ResourceManager rm;
extern class SoundManager sm;

bool collide(sf::Sprite& s1, sf::Sprite& s2, bool side[4], float offset = 3);
bool collide2(sf::Sprite& s1, sf::Sprite s2);
float abso(float i);
std::string to_string(int number);
void setCenter(sf::Text& txt, int y);

#endif // GLOBALS_H_INCLUDED
