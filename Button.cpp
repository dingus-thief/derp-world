#include "Button.h"

Button::Button(const std::string& txt, int x, int y) : x(x), y(y)
{
    buttonSprite.SetTexture(rm.getImage("button.png"));
    buttonSprite.SetPosition(x, y);
    buttonSprite.SetPosition((WIDTH)/2 - buttonSprite.GetGlobalBounds().Width/2, y);
    highlighted = false;
    text = new sf::Text(txt);
    text->SetCharacterSize(28);
    centerText();
}

void Button::center(int start, int end)
{
    buttonSprite.SetPosition((end-start)/2 - buttonSprite.GetGlobalBounds().Width/2, buttonSprite.GetPosition().y);
    centerText();
}

void Button::centerText()
{
    sf::FloatRect rect = text->GetGlobalBounds();
    text->SetPosition(static_cast<int>(buttonSprite.GetGlobalBounds().Left + buttonSprite.GetGlobalBounds().Width/2 - rect.Width/2) , static_cast<int>(buttonSprite.GetGlobalBounds().Top + buttonSprite.GetGlobalBounds().Height/2 - rect.Height/2));
}

void Button::move(int mx, int my)
{
    x += mx;
    y += my;
    buttonSprite.Move(mx, my);
    centerText();
}

void Button::setPosition(int mx, int my)
{
    x = mx;
    y = my;
    buttonSprite.SetPosition(x, y);
    centerText();
}


bool Button::isClicked(float x, float y)
{
    sf::FloatRect rect(buttonSprite.GetGlobalBounds());
    if(rect.Contains(x, y))
    {
        sm.play("click.ogg");
        return true;
    }
    return false;
}

void Button::checkHL(float x, float y)
{
    sf::FloatRect rect(buttonSprite.GetGlobalBounds());
    if(rect.Contains(x, y))
    {
        text->SetCharacterSize(34);
        highlighted = true;
    }
    else
    {
        highlighted = false;
        text->SetCharacterSize(28);
    }
    centerText();
}

void Button::draw(sf::RenderWindow* Window)
{
    Window->Draw(buttonSprite);
    if(highlighted)
        text->SetColor(sf::Color::Yellow);
    else
        text->SetColor(sf::Color::White);
    Window->Draw(*text);
}

