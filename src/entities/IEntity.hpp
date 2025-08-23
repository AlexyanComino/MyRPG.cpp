
#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

namespace MyRpg {
    class Collisions;

    typedef enum entityType {
        PAWN,
        ARCHER,
        WARRIOR,
        TNT,
        TORCH,
    } entityType;

    typedef enum entityColor {
        BLUE,
        PURPLE,
        RED,
        YELLOW,
        BLACK,
    } entityColor;

    typedef enum entityFaction {
        BLUE_TEAM,
        RED_TEAM,
        PURPLE_TEAM,
        YELLOW_TEAM,
        GOBLIN_TEAM,
        AGAINST_ALL,
        WITH_ALL,
    } entityFaction;

    typedef enum sideX {
        RIGHT,
        LEFT,
     } sideX;

    typedef enum sideY {
        NONE,
        DOWN,
        UP,
    } sideY;

    typedef enum entityState {
        IDLE,
        WALK,
        RUN,
        ST_ATT,
        ATTACK,
        ST_WORK,
        WORK,
        IDLE_CARRY,
        MOVE_CARRY,
        DEAD,
        INTERACT,
        RIEN,
    } entityState;

    class IEntity {
        public:
            ~IEntity() = default;

            virtual void update() = 0;
            virtual void display(sf::RenderWindow& window) = 0;
            virtual void handleEvents(float dt, Collisions collisionsMap, std::vector<std::unique_ptr<IEntity>>& entities) = 0;

            virtual void attack(float dt) = 0;

            virtual const sf::IntRect getHitbox() const = 0;
            virtual const sf::IntRect getAttackHitbox() const = 0;
            virtual const sf::IntRect getFeetHitbox() const = 0;

            virtual const sf::IntRect getNewFeetHitbox(const float x, const float y) const = 0;

            // Getters
            virtual const std::string& getName() const = 0;
            virtual entityType getType() const = 0;
            virtual entityColor getColor() const = 0;
            virtual entityFaction getFaction() const = 0;
            virtual entityState getState() const = 0;
            virtual float getX() const = 0;
            virtual float getY() const = 0;
            virtual float getScale() const = 0;
            virtual sideX getSideX() const = 0;
            virtual sideY getSideY() const = 0;
            virtual unsigned int getMaxHealth() const = 0;
            virtual int getHealth() const = 0;
            virtual unsigned int getAttack() const = 0;
            virtual unsigned int getDefense() const = 0;
            virtual unsigned int getXp() const = 0;
            virtual unsigned int getLevel() const = 0;
            virtual float getSpeed() const = 0;
            virtual float getAttackCooldown() const = 0;

            virtual bool isInView() const = 0;
            virtual bool isAttacking() const = 0;

            // Setters
            virtual void setX(float x) = 0;
            virtual void setY(float y) = 0;
            virtual void setScale(float scale) = 0;
            virtual void setSideX(sideX side) = 0;
            virtual void setSideY(sideY side) = 0;
            virtual void setMaxHealth(unsigned int maxHealth) = 0;
            virtual void setHealth(int health) = 0;
            virtual void setAttack(unsigned int attack) = 0;
            virtual void setDefense(unsigned int defense) = 0;
            virtual void setSpeed(float speed) = 0;
            virtual void setAttackCooldown(float cooldown) = 0;

            virtual void setInView(bool isInView) = 0;

        protected:
        private:
    };
}

#endif /* !IENTITY_HPP_ */
