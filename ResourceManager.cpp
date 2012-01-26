#include "ResourceManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
//#include <boost/lexical_cast.hpp>

ResourceManager::ResourceManager()
{
    font.LoadFromFile("Data/Fonts/GOUDYSTO.TTF");
}

sf::Texture& ResourceManager::getImage(std::string name)
{
    if(textures.find(name) != textures.end())
        return(*textures[name]);
    else
    {
        sf::Texture* img = new sf::Texture();

        if(!img->LoadFromFile("Data/Images/" + name))
            blackList.push_back(name);
        else
        {
            textures[name] = img;
        }
        return *img;
    }
}

Tile& ResourceManager::getTile(const std::string& tileID)
{
    Tile* tile = new Tile(*tiles[tileID]);
    return *tile;
}

/*void ResourceManager::loadTileset(const std::string& fileName)
{
    std::ifstream file;
    file.open(fileName.c_str());
    std::string name;
    bool solid;
    std::string buffer;
    int texAmount;
    file >> texAmount;
    getline(file, buffer); //take buffer
    for(int i = 0; i < texAmount; i++)
    {
        file >> name;
        file >> solid;
        std::cout<<name<<" "<<solid<<"\n";
        getline(file, buffer);
        tiles[boost::lexical_cast<std::string>(i+1)] = new Tile(getImage(name), solid);
    }
}*/

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

