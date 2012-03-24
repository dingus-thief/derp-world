#include "HUD.h"

HUD *HUD::m_instance = 0;

HUD::HUD() : lastScore(0), spellRectX(0), maxHealth(100), maxMana(100)
{
    coinSprite.SetTexture(rm.getImage("coin.png"));
    cointext.SetPosition(20, 10);
    cointext.SetCharacterSize(20);
    timeText.SetCharacterSize(20);

    spellMenu.SetTexture(rm.getImage("spellMenu.png"));
    spellRect.SetSize(sf::Vector2f(32, 32));
    spellRect.SetPosition(150, 0);
    spellRect.SetOutlineColor(sf::Color::Yellow);
    spellRect.SetOutlineThickness(3);
    spellRect.SetFillColor(sf::Color::Transparent);


    manaBar.SetFillColor(sf::Color::Blue);
    manaMaxBar.SetFillColor(sf::Color::Transparent);
    manaMaxBar.SetOutlineColor(sf::Color::Black);
    manaMaxBar.SetOutlineThickness(2);
    healthBar.SetFillColor(sf::Color::Red);
    healthMaxBar.SetFillColor(sf::Color::Transparent);
    healthMaxBar.SetOutlineColor(sf::Color::Black);
    healthMaxBar.SetOutlineThickness(2);
    manaMaxBar.SetSize(sf::Vector2f(100, 10));
    healthMaxBar.SetSize(sf::Vector2f(100, 10));
    timer.Start();
}

void HUD::setMaxHealth(int mHealth)
{
    maxHealth = mHealth;
}

void HUD::setMaxMana(int mMana)
{
    maxMana = mMana;
}

void HUD::reset()
{
    timer.Reset(true);
}

void HUD::pause()
{
    timer.Stop();
}

HUD* HUD::instance()
{
    if (!m_instance)
        m_instance = new HUD;
    return m_instance;
}

void HUD::resume()
{
    timer.Start();
}

HUD::~HUD()
{
    //dtor
}

void HUD::update(int health, int mana)
{
    manaBar.SetSize(sf::Vector2f(mana * (maxMana/100), 10));
    healthBar.SetSize(sf::Vector2f(health * (maxHealth/100) , 10));

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
    sf::FloatRect rect(sf::Vector2f(view.GetCenter() - sf::Vector2f(view.GetSize().x/2, view.GetSize().y/2)), sf::Vector2f(view.GetSize())); //-16 each time is because otherwise on the left side the sprite won't be drawn unless it's fully in

    cointext.SetPosition(rect.Left + 20, rect.Top +10);
    timeText.SetPosition(rect.Left + rect.Width - 20, rect.Top + 10);
    window->Draw(cointext);
    window->Draw(timeText);

    manaBar.SetPosition(rect.Left + 10, rect.Top + 10);
    manaMaxBar.SetPosition(rect.Left + 10, rect.Top + 10);
    healthBar.SetPosition(rect.Left + 10, rect.Top + 25);
    healthMaxBar.SetPosition(rect.Left + 10, rect.Top + 25);
    spellMenu.SetPosition(rect.Left + 150, rect.Top + 10);
    spellRect.SetPosition(rect.Left + 150 + spellRectX, rect.Top + 10);
    window->Draw(manaBar);
    window->Draw(manaMaxBar);
    window->Draw(healthBar);
    window->Draw(healthMaxBar);
    window->Draw(spellMenu);
    window->Draw(spellRect);
}
