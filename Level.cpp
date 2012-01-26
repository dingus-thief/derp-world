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
        propSet(bool solid = true, bool jumpthrough = false) : solid(solid), jumpThrough(jumpthrough) {};
        bool solid;
        bool jumpThrough;
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
        TiXmlElement* properties = tile->FirstChildElement("properties");
        TiXmlElement* prop = properties->FirstChildElement("property");
        while(prop != NULL)
        {
            bool solid = true, jumpthrough = false;
            std::string name = prop->Attribute("name");
            if(name == "jumpThrough")
                jumpthrough = true;
            else if(name == "solid")
                solid = false;
            pMap[id] = propSet(solid, jumpthrough);
            prop = prop->NextSiblingElement("property");
        }
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
                        tiles.push_back(Tile(sprite, pMap[subRectToUse].solid, pMap[subRectToUse].jumpThrough));
                    else
                        tiles.push_back(Tile(sprite, true, false));
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

                /*TiXmlElement *properties;
                properties = objectElement->FirstChildElement("properties");
                if (properties != NULL)
                {
                    TiXmlElement *prop;
                    prop = properties->FirstChildElement("property");
                    if (prop != NULL)
                    {
                        while(prop)
                        {
                            std::string propertyName = prop->Attribute("name");
                            std::string propertyValue = prop->Attribute("value");

                            object.properties[propertyName] = propertyValue;

                            prop = prop->NextSiblingElement("property");
                        }
                    }
                }*/

                sf::Sprite sprite;
                sprite.SetTexture(tilesetImage);
                sprite.SetTextureRect(subRects[subRectToUse]);
                sprite.SetPosition(x, HEIGHT - height*(TILESIZE+1) + y - 2);
                entities.push_back(new Entity(sprite));

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

void Level::handle(const sf::Event& event)
{

}

bool Level::tryMove(sf::Sprite& sprite, float x, float y)
{
    //out of screen? (=end/start of level)
    sf::FloatRect rect1(sprite.GetGlobalBounds().Left+x, sprite.GetGlobalBounds().Top+y, sprite.GetGlobalBounds().Width, sprite.GetGlobalBounds().Height);
    if(rect1.Left < 0 || rect1.Left + rect1.Width > width*TILESIZE)
        return false;
    sf::FloatRect intersection;
    //check collision with tiles
    for(int j = 0; j < tiles.size(); j++)
    {
        if(tiles[j].solid)
        {
            sf::FloatRect rect2(tiles[j].sprite.GetGlobalBounds());
            if(rect1.Intersects(rect2, intersection))
            {
                if(!tiles[j].jumpThrough)
                {
                    return false;
                }
                else //it's a jumpthrough tile
                {
                    if((y > 0 && rect1.Top + rect1.Height - y <= rect2.Top)) //we were going down
                    {
                        return false;
                    }
                }

            }
        }
    }
    sprite.Move(x, y);
    return true;
}


void Level::update(int frameTime)
{
    accumulator += frameTime;
    while(accumulator >= timeStep)
    {
        for(int i = 0; i < entities.size(); i++)
        {
            entities[i]->update(tiles);
        }
        accumulator -= timeStep;
    }
}


Level::~Level()
{
    //dtor
}

void Level::draw(sf::RenderWindow* window)
{
    window->Draw(background);
    for(int i = 0; i < tiles.size(); i++)
    {
        tiles[i].draw(window);
    }
    for(int i = 0; i < entities.size(); i++)
    {
        entities[i]->draw(window);
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

    if(herosprite.GetGlobalBounds().Top + herosprite.GetGlobalBounds().Height + HEIGHT/2 > (height-4)*TILESIZE)
        outOfScreenY = true;


    if(!outOfScreenY)
    {
        sf::View view = window->GetView();
        view.SetCenter(window->GetView().GetCenter().x, herosprite.GetGlobalBounds().Top + TILESIZE*4);
        window->SetView(view);
    }


    if(!outOfScreenX)
    {
        sf::View view = window->GetView();
        view.SetCenter(herosprite.GetPosition().x, window->GetView().GetCenter().y);
        background.SetPosition(herosprite.GetPosition().x - WIDTH/2, background.GetPosition().y);
        window->SetView(view);
    }

}