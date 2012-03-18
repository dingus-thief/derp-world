#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>
#include "Globals.h"
#include "Tile.h"

class Entity
{
    friend class Level;

    public:
        Entity(const std::string& name, int health, int damage, int x, int y);
        ~Entity();
        void update(const std::vector<Tile>& tiles);
        void draw(sf::RenderWindow* window);
        void onHit(unsigned damage);
        sf::FloatRect getBounds();
        bool dead;

    protected:

        int health;
        int damage;
        void move(const std::vector<Tile>& tiles);
        void handleAnimation();
        DIR previousDir;
        float speed;
        float x;
        float vely;
        DIR dir;


        float delta;
        sf::Sprite sprite;
        thor::Animator animator;
        thor::FrameAnimation::Ptr rightRunAnim, leftRunAnim, leftAttackAnim, rightAttackAnim;
};

#endif // ENTITY_H
