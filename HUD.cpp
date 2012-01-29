#include "HUD.h"

HUD::HUD() : lastScore(0)
{
    coinSprite.SetTexture(rm.getImage("coin.png"));
    cointext.SetPosition(20, 10);
    cointext.SetCharacterSize(20);
    timeText.SetCharacterSize(20);
    timer.Start();
}

void HUD::reset()
{
    timer.Reset(true);
}

HUD::~HUD()
{
    //dtor
}

void HUD::update()
{
    if(points != lastScore)
    {
        cointext.SetString(to_string(points));
        lastScore = points;
    }
    if(lastTime != timer.GetElapsedTime().AsSeconds())
    {
        timeText.SetString(to_string(timer.GetElapsedTime().AsSeconds()));
        lastTime = timer.GetElapsedTime().AsSeconds();
    }
}

void HUD::draw(sf::RenderWindow* window, const sf::FloatRect& rect)
{
    cointext.SetPosition(rect.Left + 20, rect.Top +10);
    timeText.SetPosition(rect.Left + rect.Width - 20, rect.Top + 10);
    window->Draw(cointext);
    window->Draw(timeText);
}
