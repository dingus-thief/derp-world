#include "Level.h"
#include "Tile.h"
#include "Entity.h"
#include <fstream>
#include <iostream>

Level::Level(const std::string& filename) : accumulator(0)
{
    background.SetTexture(rm.getImage("backgroundGame.png"));
    background.SetPosition(0, WIDTH-background.GetGlobalBounds().Height);
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
    std::cout<<margin<<" "<<spacing;
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
            else if(name == "coin")
                coin = true;
            prop = prop->NextSiblingElement("property");
        }
        pMap[id] = propSet(transparent, platform, kill, coin);
        tile = tile->NextSiblingElement("tile");
    }

    //Tileset image
    TiXmlElement *image;
    image = tilesetElement->FirstChildElement("image");
    std::string imagepath = image->Attribute("source");

    if (!tilesetImage.LoadFromFile(imagepath))//Load the tileset image
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
                    sprite.SetPosition(x * TILESIZE, HEIGHT - height*TILESIZE + y*TILESIZE);

                    //add tile to layer
                    if(pMap.find(subRectToUse) != pMap.end())
                    {
                        if(!pMap[subRectToUse].coin)
                            tiles.push_back(Tile(sprite, pMap[subRectToUse].transparent, pMap[subRectToUse].platform, pMap[subRectToUse].kill));
                        else
                            coins.push_back(new Coin(sprite));
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
                std::string objectType;
                if (objectElement->Attribute("type") != NULL)
                {
                    objectType = objectElement->Attribute("type");
                }
                std::string objectName;
                if (objectElement->Attribute("name") != NULL)
                {
                    objectName = objectElement->Attribute("name");
                }
                int x = atoi(objectElement->Attribute("x"));
                int y = atoi(objectElement->Attribute("y"));
                int GID = atoi(objectElement->Attribute("gid"));
                int subRectToUse = GID - firstTileID;

                bool monster = false, cannon = false;

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
                            std::string name = prop->Attribute("name");
                            if(name == "monster")
                                monster = true;
                            else if(name == "cannon")
                                cannon = true;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }

                sf::Sprite sprite;
                sprite.SetTexture(tilesetImage);
                sprite.SetTextureRect(subRects[subRectToUse]);
                sprite.SetPosition(x, HEIGHT - height*(TILESIZE+2) + y + 8);
                if(monster)
                    entities.push_back(new Entity(sprite));
                else if(cannon)
                    cannons.push_back(new Cannon(sprite));

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

Level::~Level()
{
    cannons.clear();
    bullets.clear();
    tiles.clear();
    coins.clear();
    entities.clear();
}

void Level::handle(const sf::Event& event)
{

}

void Level::reset()
{
    accumulator = 0;
    for(unsigned i = 0; i < entities.size(); i++)
        entities[i]->dead = false;
    bullets.clear();
    for(unsigned i = 0; i < cannons.size(); i++)
    {
        cannons[i]->reset();
    }
    for(unsigned i = 0; i < coins.size(); i++)
    {
        coins[i]->taken = false;
    }
    hud.reset();
    points = 0;
    background.SetPosition(0, WIDTH-background.GetGlobalBounds().Height);
    gameover = false;
}

void Level::update(int frameTime)
{
    hud.update();
    accumulator += frameTime;
    while(accumulator >= timeStep)
    {
        for(unsigned i = 0; i < entities.size(); i++)
        {
            entities[i]->update(tiles);
        }
        for(unsigned i = 0; i < cannons.size(); i++)
        {
            cannons[i]->update(bullets);
        }
        std::list<Bullet*>::iterator itr = bullets.begin();
        while(itr != bullets.end())
        {
            if((*itr)->dead)
            {
                bullets.erase(itr++);
                continue;
            }
            else
                (*itr)->update();

            itr++;
        }
        accumulator -= timeStep;
    }
}


void Level::draw(sf::RenderWindow* window)
{

    sf::View view = window->GetView();
    sf::FloatRect viewport(sf::Vector2f(view.GetCenter() - sf::Vector2f(view.GetSize().x/2 + 16, view.GetSize().y/2)), sf::Vector2f(view.GetSize()) + sf::Vector2f(16, 0)); //-16 each time is because otherwise on the left side the sprite won't be drawn unless it's fully in

    background.SetPosition(viewport.Left+16, viewport.Top);
    window->Draw(background);
    hud.draw(window, viewport);
    for(unsigned i = 0; i < tiles.size(); i++)
    {
        if(viewport.Contains(tiles[i].sprite.GetGlobalBounds().Left, tiles[i].sprite.GetGlobalBounds().Top) || viewport.Intersects(tiles[i].sprite.GetGlobalBounds()))
            tiles[i].draw(window);
    }
    for(unsigned i = 0; i < entities.size(); i++)
    {
        entities[i]->draw(window);
    }
    for(unsigned i = 0; i < cannons.size(); i++)
    {
        cannons[i]->draw(window);
    }
    for(unsigned i = 0; i < coins.size(); i++)
    {
        coins[i]->draw(window);
    }
    std::list<Bullet*>::iterator itr = bullets.begin();
    while(itr != bullets.end())
    {
        (*itr)->draw(window);
        itr++;
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

    if(!outOfScreenX)
    {
        sf::View view = window->GetView();
        view.SetCenter(static_cast<int>(herosprite.GetPosition().x), static_cast<int>(window->GetView().GetCenter().y));
        window->SetView(view);
    }

    if(herosprite.GetGlobalBounds().Top + 78 > HEIGHT/2)
    {
        sf::View view = window->GetView();
        view.SetCenter(static_cast<int>(window->GetView().GetCenter().x), static_cast<int>(HEIGHT/2));
        window->SetView(view);
        return;
    }

    if(!outOfScreenY);
    {
        sf::View view = window->GetView();
        view.SetCenter(static_cast<int>(window->GetView().GetCenter().x), static_cast<int>(herosprite.GetGlobalBounds().Top+ 78));
        window->SetView(view);
    }
}
