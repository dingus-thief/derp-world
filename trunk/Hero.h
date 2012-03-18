#ifndef HERO_H
#define HERO_H
#include <SFML/Graphics.hpp>
#include <Thor/Animation.hpp>
#include "Globals.h"
#include "Level.h"
#include "FireSpell.h"
#include "GreenSpell.h"
#include "IceSpell.h"
#include <Thor/Time/Timer.hpp>

struct HeroState
{
    HeroState() : dir(DIR::RIGHT), walking(false), falling(true), jumping(false), idle(false){};
    bool operator!=(const HeroState &other) const {
    return !(dir == other.dir && walking == other.walking && jumping == other.jumping && falling == other.falling && idle == other.idle);
  }
    DIR dir;
    bool walking;
    bool falling;
    bool jumping;
    bool idle;
};

enum spell{fire, ice, green};

class Hero
{
    public:
        Hero();
        ~Hero();
        void draw(sf::RenderWindow* window);
        void update(int frameTime, Level* level);
        void handle(const sf::Event& event);
        void reset(Level* level);
        void shoot();
        sf::Sprite sprite;


    private:
        bool tryMove(Level* level, float x, float y);
        void handleAnimation(int frameTime);
        void deleteDestroyedSpells();
        void spellCollisions(Level* level);
        void initAnimation();
        void execGravity(Level* level);
        void execInput(Level* level);
        void updateBars();
        int accumulator;
        HeroState currState, oldState;
        thor::FrameAnimation::Ptr leftRunAnim, rightRunAnim, leftJumpAnim, rightJumpAnim, leftIdleAnim, rightIdleAnim;
        thor::Animator animator;
        std::list<Spell*> spells;
        spell currentSpell;
        int maxHealth;
        float health;
        int maxMana;
        float mana;
        sf::RectangleShape manaBar;
        sf::RectangleShape healthBar;
        float dx;
        float dy;
        float speed;
};

#endif // HERO_H
