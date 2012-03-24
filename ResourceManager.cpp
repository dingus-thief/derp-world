#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
//#include <boost/lexical_cast.hpp>

ResourceManager::ResourceManager()
{
    font.LoadFromFile("Data/Fonts/visitor.TTF");
}

sf::Texture& ResourceManager::getImage(const std::string& name)
{
    if(textures.find(name) != textures.end())
        return(*textures[name]);
    else
    {
        sf::Texture* img = new sf::Texture();
        //img->SetSmooth(false);

        if(!img->LoadFromFile("Data/Images/" + name))
            blackList.push_back(name);
        else
        {
            textures[name] = img;
        }
        return *img;
    }
}

sf::SoundBuffer& ResourceManager::getSoundBuffer(const std::string& name)
{
    if(buffers.find(name) != buffers.end())
        return(*buffers[name]);
    else
    {
        sf::SoundBuffer* img = new sf::SoundBuffer();
        //img->SetSmooth(false);

        if(!img->LoadFromFile("Data/Audio/" + name))
            blackList.push_back(name);
        else
        {
            buffers[name] = img;
        }
        return *img;
    }
}


void ResourceManager::storeImageAs(const std::string& fileName, const std::string& alias)
{
    if(textures.find(alias) == textures.end())
    {
        sf::Texture* img = new sf::Texture;
        std::cout<<fileName<<" "<<alias<<"\n";
        img->LoadFromFile("Data/Images/" + fileName);
        textures[alias] = img;
    }
}

sf::Text& ResourceManager::getText(std::string string, int fontSize, float x, float y, sf::Color color)
{
    sf::Text* text = new sf::Text;
    text->SetString(string);
    text->SetCharacterSize(fontSize);
    text->SetFont(font);
    text->SetColor(color);
    text->SetPosition(x, y);
    return *text;
}

ResourceManager::~ResourceManager()
{
    //dtor
}

bool ResourceManager::isValid(std::string name)
{
    for(std::list<std::string>::iterator itr = blackList.begin(); itr != blackList.end(); itr++)
    if(*itr == name)
        return false;
    return true;
}

