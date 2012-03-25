#include "Bat.h"

Bat::Bat(int x, int y) : Entity("bat.png", 30, 20, x, y)
{
    xp = 10;
    xpText = rm.getText("+10", 13);

    flying = true;
    speed = 0.6;

    for(int i = 0; i < 29*2; i+=29)
        rightRunAnim->AddFrame(1.f, sf::IntRect(i, 0, 28, 24));
    for(int i = 0; i < 29*2; i+=29)
        leftRunAnim->AddFrame(1.f, sf::IntRect(i, 25, 28, 24));

    animator.AddAnimation("leftRunning", leftRunAnim, sf::Seconds(0.2));
    animator.AddAnimation("rightRunning", rightRunAnim, sf::Seconds(0.2));
    animator.PlayAnimation("leftRunning", true);

    fireEffectiveness = 2;
    iceEffectiveness = 0.3;
    energyEffectiveness = 0.3;
}

Bat::~Bat()
{
    //dtor
}
