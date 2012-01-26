#ifndef ResourceManager_H
#define ResourceManager_H
#include <map>
#include <list>
#include <SFML/Graphics.hpp>
#include "Tile.h"

class ResourceManager
{
    public:
        ResourceManager();
        ~ResourceManager();

        sf::Texture& getImage(std::string name);
        void storeImageAs(const std::string& fileName, const std::string& alias);
        sf::Text& getText(std::string string, int fontSize = 25, float x = 0, float y = 0, sf::Color color = sf::Color::White);
        void loadTileset(const std::string& fileName);
        Tile& getTile(const std::string& tileID);

    private:
        std::map<std::string, sf::Texture*> textures;
        std::map<std::string, Tile*> tiles;
        std::list<std::string> blackList;

        bool isValid(std::string name);
        sf::Font font;
};

#endif // ResourceManager_H
