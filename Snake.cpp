#include "Snake.h"

Snake::Snake(int x, int y) : Entity("snake.png", 75, 10, x, y)
{
    xp = 5;
    xpText = rm.getText("+5", 13);

    speed = 0.2;

    for(int i = 0; i < 33*2; i+=33)
        leftRunAnim->AddFrame(1.f, sf::IntRect(i, 0, 32, 32));
    for(int i = 0; i < 32*2; i+=33)
        rightRunAnim->AddFrame(1.f, sf::IntRect(i, 32, 32, 32));

    animator.AddAnimation("leftRunning", leftRunAnim, sf::Seconds(0.2));
    animator.AddAnimation("rightRunning", rightRunAnim, sf::Seconds(0.2));
    animator.PlayAnimation("leftRunning", true);

    fireEffectiveness = 1;
    iceEffectiveness = 2;
    energyEffectiveness = 1;
}

Snake::~Snake()
{
    //dtor
}
