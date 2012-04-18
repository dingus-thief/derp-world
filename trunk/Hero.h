#ifndef HERO_H
#define HERO_H
#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>
#include "Globals.h"
#include "Constants.h"
#include "Level.h"
#include "FireSpell.h"
#include "GreenSpell.h"
#include "IcicleSpell.h"
#include "FireBallSpell.h"
#include "IceSpell.h"
#include <Thor/Time/Timer.hpp>
#include <fstream>
#include "HUD.h"

struct HeroState
{
    HeroState() : dir(DIR::RIGHT), walking(false), falling(true), jumping(false), idle(false) {};
    bool operator!=(const HeroState &other) const
    {
        return !(dir == other.dir && walking == other.walking && jumping == other.jumping && falling == other.falling && idle == other.idle);
    }
    DIR dir;
    bool walking;
    bool falling;
    bool jumping;
    bool idle;
};

class Hero
{
    public:
        Hero(HUD* hud);
        ~Hero();
        void draw(sf::RenderWindow* window);
        void update(int frameTime, Level* level);
        void handle(const sf::Event& event);
        void reset(sf::Vector2f vec);
        void shoot();
        sf::FloatRect getBounds();
        int getLivesLeft();
        sf::Sprite sprite;


    private:
        void load(const std::string& filePath);
        bool tryMove(Level* level, float x, float y);
        void handleAnimation(int frameTime);
        void deleteDestroyedSpells();
        void onDead();
        void spellCollisions(Level* level);
        void initAnimation();
        void execGravity(Level* level);
        void execInput(Level* level);
        void regenerateMana();
        void checkPlatforms(std::vector<MovingTile> platforms);
        void checkItems(std::vector<Item>& items);
        int accumulator;
        HeroState currState, oldState;
        thor::FrameAnimation::Ptr leftRunAnim, rightRunAnim, leftJumpAnim, rightJumpAnim, leftIdleAnim, rightIdleAnim, leftShootAnim, rightShootAnim;
        thor::Animator animator;
        std::list<Spell*> spells;
        Spell* currentSpell;
        HUD* hud;
        sf::Clock shootClock;
        int lives;
        int maxLives;
        int maxMana;
        float mana;
        bool onPlatform;
        bool dead;
        float dx;
        float dy;
        float deathy;
        float speed;
        int fireSkill;
        int iceSkill;
        int energySkill;
        int heroLevel;
        int xp;
        int jumpPower;
        sf::Vector2f platformSpeed;
        std::string name;
};

#endif // HERO_H
