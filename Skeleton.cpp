#include "Skeleton.h"

Skeleton::Skeleton(int x, int y) : Entity("skeleton.png", 50, 10, x, y)
{
    for(int i = 0; i < 32*3; i+=32)
        rightRunAnim->AddFrame(1.f, sf::IntRect(i, 0, 32, 42));
    for(int i = 0; i < 32*3; i+=32)
        leftRunAnim->AddFrame(1.f, sf::IntRect(i, 42, 32, 42));

    animator.AddAnimation("leftRunning", leftRunAnim, sf::Seconds(0.5));
    animator.AddAnimation("rightRunning", rightRunAnim, sf::Seconds(0.5));
    animator.PlayAnimation("leftRunning");

    sprite.SetTextureRect(sf::IntRect(32, 0, 32, 42));
}

Skeleton::~Skeleton()
{
    //dtor
}
