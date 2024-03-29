#include "Level.h"
#include "Tile.h"
#include <fstream>
#include <iostream>

Level::Level(const std::string& filename) : accumulator(0), lastCheckpoint(10, 75), filename(filename)//, thread(&Level::loadFromFile, this)
{
    background.SetTexture(rm.getImage("backgroundGame.png"));
    background.SetPosition(0, WIDTH-background.GetGlobalBounds().Height);
    loadFromFile();

    //loadFromFile(filename);
    //thread.Launch();
}

Level::~Level()
{
    for(auto itr = entities.begin(); itr != entities.end(); itr++)
        delete (*itr);
    for(auto itr = coins.begin(); itr != coins.end(); itr++)
        delete (*itr);

    entities.clear();
    coins.clear();
    tiles.clear();
    movingTiles.clear();
    spikes.clear();
    coins.clear();
    entities.clear();
    flyBlocks.clear();
    platformBlocks.clear();
}

void Level::handle(const sf::Event& event)
{

}

void Level::loadFromFile()
{
    class propSet
    {
        public:
            propSet(bool transparent = false, bool platform = false, bool kill = false, bool coin = false) : transparent(transparent), platform(platform), kill(kill), coin(coin) {};
            bool transparent;
            bool platform;
            bool kill;
            bool coin;
    };
    std::map<int, propSet> pMap;

    TiXmlDocument levelFile(filename.c_str());
    if (!levelFile.LoadFile())
    {
        std::cout << "Loading level \"" << filename << "\" failed." << std::endl;
        return;
    }
    //Map element. This is the root element for the whole file.
    TiXmlElement *map;
    map = levelFile.FirstChildElement("map");

    //Set up misc map properties.
    width = atoi(map->Attribute("width"));
    height = atoi(map->Attribute("height"));

    //Tileset stuff
    TiXmlElement *tilesetElement;
    tilesetElement = map->FirstChildElement("tileset");
    int spacing = atoi(tilesetElement->Attribute("spacing"));
    int margin = atoi(tilesetElement->Attribute("margin"));
    firstTileID = atoi(tilesetElement->Attribute("firstgid"));

    TiXmlElement* tile = tilesetElement->FirstChildElement("tile");
    while(tile != NULL)
    {
        int id = atoi(tile->Attribute("id"));
        bool transparent = false, platform = false, kill = false, coin = false;
        TiXmlElement* properties = tile->FirstChildElement("properties");
        TiXmlElement* prop = properties->FirstChildElement("property");
        while(prop != NULL)
        {
            std::string name = prop->Attribute("name");
            if(name == "platform")
                platform = true;
            else if(name == "transparent")
                transparent = true;
            else if(name == "kill")
                kill = true;
            prop = prop->NextSiblingElement("property");
        }
        pMap[id] = propSet(transparent, platform, kill, coin);
        tile = tile->NextSiblingElement("tile");
    }

    //Tileset image
    TiXmlElement *image;
    image = tilesetElement->FirstChildElement("image");
    //std::string imagepath = image->Attribute("source");

    if (!tilesetImage.LoadFromFile("Data/Images/tileset.png"))//Load the tileset image
    {
        std::cout << "Failed to load tile sheet." << std::endl;
        return;
    }

    //tilesetImage.CreateMaskFromColor(sf::Color(255, 0, 255));
    tilesetImage.SetSmooth(false);

    //Columns and rows (of tileset image)
    int columns = tilesetImage.GetWidth() / (TILESIZE+spacing);
    int rows = tilesetImage.GetHeight() / (TILESIZE+spacing);

    std::vector <sf::Rect<int> > subRects;//container of subrects (to divide the tilesheet image up)

    //tiles/subrects are counted from 0, left to right, top to bottom
    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            sf::Rect <int> rect;
            rect.Top = y * (TILESIZE+spacing) + margin;
            rect.Width = TILESIZE;
            rect.Left = x * (TILESIZE+spacing) + margin;
            rect.Height = TILESIZE;
            subRects.push_back(rect);
        }
    }

    //Layers
    TiXmlElement *layerElement;
    layerElement = map->FirstChildElement("layer");
    while (layerElement)
    {
        //Tiles
        TiXmlElement *layerDataElement;
        layerDataElement = layerElement->FirstChildElement("data");

        if (layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if (tileElement == NULL)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
            return;
        }

        int x = 0;
        int y = 0;

        while (tileElement)
        {
            int tileGID = atoi(tileElement->Attribute("gid"));
            int subRectToUse = tileGID - firstTileID;//Work out the subrect ID to 'chop up' the tilesheet image.
            if (subRectToUse >= 0)//we only need to (and only can) create a sprite/tile if there is one to display
            {
                if(tileGID != 0)
                {

                    sf::Sprite sprite;//sprite for the tile
                    sprite.SetTexture(tilesetImage);
                    sprite.SetTextureRect(subRects[subRectToUse]);
                    sprite.SetPosition(x * TILESIZE, y * TILESIZE);

                    //add tile to layer
                    if(pMap.find(subRectToUse) != pMap.end())
                    {
                        tiles.push_back(Tile(sprite, pMap[subRectToUse].transparent, pMap[subRectToUse].platform, pMap[subRectToUse].kill));
                    }
                    else
                        tiles.push_back(Tile(sprite, false, false, false));
                }
            }

            tileElement = tileElement->NextSiblingElement("tile");

            //increment x, y
            x++;
            if (x >= width)//if x has "hit" the end (right) of the map, reset it to the start (left)
            {
                x = 0;
                y++;
                if (y >= height)
                {
                    y = 0;
                }
            }
        }
        layerElement = layerElement->NextSiblingElement("layer");
    }

    //Objects

    TiXmlElement *objectGroupElement;
    if (map->FirstChildElement("objectgroup") != NULL)//Check that there is atleast one object layer
    {
        objectGroupElement = map->FirstChildElement("objectgroup");
        while (objectGroupElement)//loop through object layers
        {
            TiXmlElement *objectElement;
            objectElement = objectGroupElement->FirstChildElement("object");
            while (objectElement)//loop through objects
            {
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));

                std::string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    std::string name = objectElement->Attribute("name");
                    if(name == "movingPlatform")
                    {
                        float deltax = 0;
                        float deltay = 0;
                        TiXmlElement *properties;
                        properties = objectElement->FirstChildElement("properties");
                        if (properties != NULL)
                        {
                            TiXmlElement *prop;
                            prop = properties->FirstChildElement("property");
                            if (prop != NULL)
                            {
                                while(prop)
                                {
                                    std::string propName = prop->Attribute("name");
                                    if(propName == "x")
                                        deltax = atof(prop->Attribute("value"));
                                    else if(propName == "y")
                                        deltay = atof(prop->Attribute("value"));

                                    prop = prop->NextSiblingElement("property");
                                }
                            }
                        }
                        sf::Sprite sprite;
                        sprite.SetTexture(rm.getImage("platform.png"));
                        sprite.SetPosition(x, y);
                        movingTiles.push_back(MovingTile(sprite, false, true, false, deltax, deltay));
                    }

                    else if(name == "skeleton")
                        entities.push_back(new Skeleton(x, y - 10));
                    else if(name == "bat")
                        entities.push_back(new Bat(x, y+2));
                    else if(name == "snake")
                        entities.push_back(new Snake(x, y));
                    else if(name == "flyBlock")
                        flyBlocks.push_back(sf::FloatRect(x, y, 32, 32));
                    else if(name == "platformBlock")
                        platformBlocks.push_back(sf::FloatRect(x, y, 32, 32));
                    else if(name == "coin")
                        coins.push_back(new Coin(x, y));
                    else if(name == "spike")
                        spikes.push_back(FallingSpike(x, y));
                    else if(name == "manaPotion")
                        items.push_back(Item(x, y, ItemType::manaPotion));
                    else if(name == "healthPotion")
                        items.push_back(Item(x, y, ItemType::healthPotion));
                }

                objectElement = objectElement->NextSiblingElement("object");
            }
            objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
        }
    }
    else
    {
        std::cout << "No object layers found..." << std::endl;
    }
    return;
}

void Level::reset()
{
    accumulator = 0;
    for(unsigned i = 0; i < entities.size(); i++)
        entities[i]->reset();
    for(unsigned i = 0; i < items.size(); i++)
        items[i].reset();
    for(unsigned i = 0; i < spikes.size(); i++)
        spikes[i].reset();
    for(unsigned i = 0; i < coins.size(); i++)
    {
        coins[i]->taken = false;
    }
    points = 0;
    background.SetPosition(0, WIDTH-background.GetGlobalBounds().Height);
}

void Level::update(int frameTime, sf::FloatRect heroRect)
{

    accumulator += frameTime;
    while(accumulator >= timeStep)
    {
        for(unsigned i = 0; i < entities.size(); i++)
        {
            entities[i]->update(tiles, flyBlocks);
        }
        for(unsigned i = 0; i < movingTiles.size(); i++)
        {
            movingTiles[i].update(platformBlocks);
        }
        for(unsigned i = 0; i < spikes.size(); i++)
        {
            spikes[i].update(heroRect, tiles);
        }
        accumulator -= timeStep;
    }
}

sf::Vector2f Level::getLastCheckpoint()
{
    return lastCheckpoint;
}


void Level::draw(sf::RenderWindow* window)
{
    sf::View view = window->GetView();
    sf::FloatRect viewport(sf::Vector2f(view.GetCenter() - sf::Vector2f(view.GetSize().x/2 + 16, view.GetSize().y/2)), sf::Vector2f(view.GetSize()) + sf::Vector2f(16, 0)); //-16 each time is because otherwise on the left side the sprite won't be drawn unless it's fully in

    background.SetPosition(viewport.Left+16, viewport.Top);
    window->Draw(background);
    for(unsigned i = 0; i < tiles.size(); i++)
    {
        if(viewport.Contains(tiles[i].sprite.GetGlobalBounds().Left, tiles[i].sprite.GetGlobalBounds().Top) || viewport.Intersects(tiles[i].sprite.GetGlobalBounds()))
            tiles[i].draw(window);
    }
    for(unsigned i = 0; i < movingTiles.size(); i++)
    {
        if(viewport.Contains(movingTiles[i].sprite.GetGlobalBounds().Left, movingTiles[i].sprite.GetGlobalBounds().Top) || viewport.Intersects(movingTiles[i].sprite.GetGlobalBounds()))
            movingTiles[i].draw(window);
    }
    for(unsigned i = 0; i < entities.size(); i++)
    {
        entities[i]->draw(window);
    }
    for(unsigned i = 0; i < coins.size(); i++)
    {
        coins[i]->draw(window);
    }
    for(unsigned i = 0; i < spikes.size(); i++)
    {
        spikes[i].draw(window);
    }
    for(unsigned i = 0; i < items.size(); i++)
    {
        items[i].draw(window);
    }
}

void Level::adjustView(sf::RenderWindow* window, const sf::Sprite& herosprite) //rect = hero sprite
{

    bool outOfScreenY = false;
    bool outOfScreenX = false;

    if(herosprite.GetGlobalBounds().Left - WIDTH/2 < 0)
        outOfScreenX = true;

    if(herosprite.GetGlobalBounds().Left + WIDTH/2 > width*TILESIZE)
        outOfScreenX = true;

    if(herosprite.GetGlobalBounds().Top + 50 + HEIGHT/2 > height*TILESIZE)
    {
        sf::View view = window->GetView();
        view.SetCenter(view.GetCenter().x, static_cast<int>(height*TILESIZE - HEIGHT/2));
        window->SetView(view);
    }
    else
    {
        sf::View view = window->GetView();
        view.SetCenter(view.GetCenter().x, static_cast<int>(herosprite.GetGlobalBounds().Top + 50));
        window->SetView(view);
    }

    if(herosprite.GetGlobalBounds().Top + 50 - HEIGHT/2 < 0)
    {
        sf::View view = window->GetView();
        view.SetCenter(view.GetCenter().x, HEIGHT/2);
        window->SetView(view);
    }


    if(!outOfScreenX)
    {
        sf::View view = window->GetView();
        view.SetCenter(static_cast<int>(herosprite.GetPosition().x), static_cast<int>(window->GetView().GetCenter().y));
        window->SetView(view);
    }

}
