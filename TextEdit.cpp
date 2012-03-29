#include "TextEdit.h"

TextEdit::TextEdit(int x, int y, int width) : width(width), focused(false)
{
    textBox = sf::RectangleShape(sf::Vector2f(width, 25));
    textBox.SetPosition(sf::Vector2f(x, y));
    text = rm.getText("", 15);
    text.SetPosition(sf::Vector2f(x+5, y+4));
    text.SetColor(sf::Color::Black);

    textBox.SetOutlineColor(sf::Color::Black);
    textBox.SetOutlineThickness(3);
}

TextEdit::~TextEdit()
{

}

void TextEdit::draw(sf::RenderWindow* window)
{
    window->Draw(textBox);
    window->Draw(text);
}

void TextEdit::checkClick(float x, float y)
{
    focused = false;
    textBox.SetOutlineColor(sf::Color::Black);
    sf::FloatRect rect(textBox.GetGlobalBounds());
    if(rect.Contains(x, y))
    {
        textBox.SetOutlineColor(sf::Color(0, 130, 19));
        focused = true;
    }
}

void TextEdit::handleBackspace()
{
    if(!text.GetString().IsEmpty())
    {
        std::string str = text.GetString().ToAnsiString();
        str = str.substr(0, str.size() - 1);
        text.SetString(sf::String(str));
    }
}

std::string TextEdit::getText()
{
    return text.GetString().ToAnsiString();
}

void TextEdit::handleEvent(const sf::Event& event, sf::RenderWindow* window)
{
    if(focused)
        if(event.Type == sf::Event::TextEntered)
            if(event.Text.Unicode > 0x1f && event.Text.Unicode != 0x7f) // not a control character?
                text.SetString(text.GetString() + sf::String(event.Text.Unicode));

    if(event.Type == sf::Event::MouseButtonPressed)
        checkClick(sf::Mouse::GetPosition(*window).x, sf::Mouse::GetPosition(*window).y);

    if(focused)
        if(event.Type == sf::Event::KeyPressed)
            if(event.Key.Code == sf::Keyboard::Back)
                handleBackspace();
}
