#include "HUD.h"

HUD::HUD() : lastScore(0), spellRectX(0), maxMana(100), maxXp(100)
{
    coinSprite.SetTexture(rm.getImage("coin.png"));
    cointext.SetPosition(20, 10);
    cointext.SetCharacterSize(20);
    timeText.SetCharacterSize(20);
    heart.SetTexture(rm.getImage("heart.png"));
    emptyheart.SetTexture(rm.getImage("emptyHeart.png"));

    spellMenu.SetTexture(rm.getImage("spellMenu.png"));
    spellRect.SetSize(sf::Vector2f(32, 32));
    spellRect.SetPosition(150, 0);
    spellRect.SetOutlineColor(sf::Color::Yellow);
    spellRect.SetOutlineThickness(3);
    spellRect.SetFillColor(sf::Color::Transparent);

    xpBar.SetFillColor(sf::Color::Green);
    xpMaxBar.SetFillColor(sf::Color::Transparent);
    xpMaxBar.SetOutlineColor(sf::Color::Black);
    xpMaxBar.SetOutlineThickness(2);

    manaBar.SetFillColor(sf::Color::Blue);
    manaMaxBar.SetFillColor(sf::Color::Transparent);
    manaMaxBar.SetOutlineColor(sf::Color::Black);
    manaMaxBar.SetOutlineThickness(2);

    manaMaxBar.SetSize(sf::Vector2f(100, 10));
    xpMaxBar.SetSize(sf::Vector2f(100, 10));
    xpBar.SetSize(sf::Vector2f(0, 10));
    timer.Start();
}

void HUD::setMaxMana(int mMana)
{
    maxMana = mMana;
}

void HUD::setMaxXp(int mXp)
{
    maxXp = mXp;
}

void HUD::setMaxLives(int mLives)
{
    maxLives = mLives;
}

void HUD::setMana(int mMana)
{
    manaBar.SetSize(sf::Vector2f(mMana * (maxMana/100), 10));
}

void HUD::setLives(int mLives)
{
    liveCount = mLives;
}

void HUD::addXp(int mxp)
{
    xpBar.SetSize(sf::Vector2f(xpBar.GetSize().x + mxp * (maxXp/100), 10));
}

void HUD::reset()
{
    timer.Reset(true);
}

void HUD::pause()
{
    timer.Stop();
}

void HUD::resume()
{
    timer.Start();
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

void HUD::draw(sf::RenderWindow* window)
{
    sf::View view = window->GetView();
    sf::FloatRect rect(sf::Vector2f(view.GetCenter() - sf::Vector2f(view.GetSize().x/2, view.GetSize().y/2)), sf::Vector2f(view.GetSize()));

    cointext.SetPosition(rect.Left + 20, rect.Top +10);
    timeText.SetPosition(rect.Left + rect.Width - 30, rect.Top + 10);
    window->Draw(cointext);
    window->Draw(timeText);

    manaBar.SetPosition(rect.Left + 10, rect.Top + 10);
    xpBar.SetPosition(rect.Left + 10, rect.Top + 25);
    manaMaxBar.SetPosition(rect.Left + 10, rect.Top + 10);
    xpMaxBar.SetPosition(rect.Left + 10, rect.Top + 25);

    int i = rect.Left + 10;
    for(; i < rect.Left + 10 + 19*liveCount; i += 19)
    {
        heart.SetPosition(i, rect.Top + 40);
        window->Draw(heart);
    }
    for(; i < rect.Left + 10 + 19*(maxLives - liveCount); i += 19)
    {
        emptyheart.SetPosition(i, rect.Top + 40);
        window->Draw(emptyheart);
    }
    spellMenu.SetPosition(rect.Left + 150, rect.Top + 10);
    spellRect.SetPosition(rect.Left + 150 + spellRectX, rect.Top + 10);
    window->Draw(manaBar);
    window->Draw(xpBar);
    window->Draw(manaMaxBar);
    window->Draw(xpMaxBar);
    window->Draw(spellMenu);
    window->Draw(spellRect);
}
