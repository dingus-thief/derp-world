#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED
#include <cmath>

enum spell {fire, ice, green, icicle};

const int WIDTH = 640;
const int HEIGHT = 480;
const int TILESIZE = 32;
const float timeStep = 10; //float because it is easier for calculations of speed & stuff

const float tsAdjuster = timeStep/5.f;

const float gravity = (2/3) * tsAdjuster;

const float MAXVEL = 5.f * tsAdjuster;
const float ACCEL = (1.f/19.f) * (tsAdjuster*tsAdjuster); // 1/19 * (timeStep/5)



//int xpNeededForLevel[10] = {10, 26, 50, 86, 125, 0, 0, 0, 0, 0};

#endif // CONSTANTS_H_INCLUDED
