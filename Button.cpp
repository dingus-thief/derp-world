#include "Button.h"

Button::Button(const std::string& txt, int x, int y)
{
    buttonSprite.SetTexture(rm.getImage("button.png"));
    buttonSprite.SetPosition((WIDTH)/2 - buttonSprite.GetGlobalBounds().Width/2, y);
    highlighted = false;
    text = rm.getText(txt, 13);
    sf::FloatRect rect = text.GetGlobalBounds();
    text.SetPosition((WIDTH)/2 - rect.Width/2 , y + buttonSprite.GetGlobalBounds().Height/2 - rect.Height/2);
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
        highlighted = true;
    else
        highlighted = false;
}

void Button::draw(sf::RenderWindow* Window)
{
    Window->Draw(buttonSprite);
    if(highlighted)
        text.SetColor(sf::Color::Yellow);
    else
        text.SetColor(sf::Color::White);
    Window->Draw(text);
}

