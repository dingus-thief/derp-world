#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>
#include "Globals.h"
#include "Tile.h"
#include "Constants.h"
#include "HUD.h"

class Entity
{
    friend class Level;

    public:
        Entity(const std::string& name, int health, int damage, int x, int y);
        ~Entity();
        void update(const std::vector<Tile>& tiles, const std::list<sf::FloatRect>& flyBlocks);
        void draw(sf::RenderWindow* window);
        void onHit(unsigned damage, spell spellType);
        void reset();
        sf::FloatRect getBounds();
        bool dead;
        bool flying;
        bool attacking;
        int damage;
        int xp;
        sf::Text xpText;
        DIR dir;

    protected:

        int health;
        int maxHealth;
        bool isHit;
        float fireEffectiveness;
        float iceEffectiveness;
        float energyEffectiveness;
        void move(const std::vector<Tile>& tiles, const std::list<sf::FloatRect>& flyBlocks);
        void handleAnimation();
        void updateHealthBar();
        DIR previousDir;
        float speed;
        float vely;
        int originalX, originalY;

        sf::RectangleShape healthRect;
        sf::RectangleShape maxHealthRect;

        float delta;
        sf::Sprite sprite;
        thor::Animator animator;
        thor::FrameAnimation::Ptr rightRunAnim, leftRunAnim, leftAttackAnim, rightAttackAnim;
};

#endif // ENTITY_H
