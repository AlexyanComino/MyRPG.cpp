
#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include <string>

#include "IEntity.hpp"
#include "Utils.hpp"
#include "Collisions.hpp"

namespace MyRpg {

    class AEntity : public IEntity {
        public:
            AEntity(const std::string& name, entityType type, entityColor color, entityFaction faction,
                    entityState state, float initX, float initY, float scale, unsigned int max_health,
                    int health, unsigned int attack, unsigned int defense, float speed,
                    unsigned int xp, unsigned int level, float attackCooldown,
                    const std::string& spritePath, int spriteWidth, int spriteHeight)
                : _name(name), _type(type), _color(color), _faction(faction), _state(state),
                  _initX(initX), _initY(initY), _x(initX), _y(initY), _scale(scale),
                  _sideX(RIGHT), _sideY(NONE), _max_health(max_health), _health(health),
                  _attack(attack), _defense(defense), _speed(speed), _xp(xp), _level(level),
                  _attackCooldown(attackCooldown), _animation(spritePath, spriteWidth, spriteHeight) {};
            ~AEntity() = default;

            virtual void update() = 0;
            virtual void display(sf::RenderWindow& window) = 0;
            void handleEvents(float dt, Collisions collisionsMap, std::vector<std::unique_ptr<IEntity>>& entities) override { return; }; // Empty implementation

            virtual void attack(float dt) = 0;

            virtual const sf::IntRect getHitbox() const = 0;
            virtual const sf::IntRect getAttackHitbox() const = 0;
            virtual const sf::IntRect getFeetHitbox() const = 0;

            virtual const sf::IntRect getNewFeetHitbox(const float x, const float y) const = 0;

            void updateSpriteScale();

            // Getters
            const std::string& getName() const override { return _name; }
            entityType getType() const override { return _type; }
            entityColor getColor() const override { return _color; }
            entityFaction getFaction() const override { return _faction; }
            entityState getState() const override { return _state; }
            float getX() const { return _x; }
            float getY() const override { return _y; }
            float getScale() const override { return _scale; }
            sideX getSideX() const override { return _sideX; }
            sideY getSideY() const override { return _sideY; }
            unsigned int getMaxHealth() const override { return _max_health; }
            int getHealth() const override { return _health; }
            unsigned int getAttack() const override { return _attack; }
            unsigned int getDefense() const override { return _defense; }
            unsigned int getXp() const override { return _xp; }
            unsigned int getLevel() const override { return _level; }
            float getSpeed() const override { return _speed; }
            float getAttackCooldown() const override { return _attackCooldown; }

            bool isInView() const override { return _inView; };
            bool isAttacking() const override { return (_state == ATTACK || _state == ST_ATT); };

            // Setters
            void setX(float x) override { this->_x = x; }
            void setY(float y) override { this->_y = y; }
            void setScale(float scale) override { this->_scale = scale; }
            void setSideX(sideX side) override { this->_sideX = side; }
            void setSideY(sideY side) override { this->_sideY = side; }
            void setMaxHealth(unsigned int maxHealth) override { this->_max_health = maxHealth; }
            void setHealth(int health) override { this->_health = health; }
            void setAttack(unsigned int attack) override { this->_attack = attack; }
            void setDefense(unsigned int defense) override { this->_defense = defense; }
            void setSpeed(float speed) override { this->_speed = speed; }
            void setAttackCooldown(float cooldown) override { this->_attackCooldown = cooldown; }

            void setInView(bool isInView) override { _inView = isInView; };

        protected:
            const std::string _name;
            const entityType _type;
            const entityColor _color;
            const entityFaction _faction;
            entityState _state;

            const float _initX;
            const float _initY;
            float _x;
            float _y;

            float _scale;

            bool _inView;

            sideX _sideX;
            sideY _sideY;

            unsigned int _max_health;
            int _health;
            unsigned int _attack;
            unsigned int _defense;
            unsigned int _xp;
            unsigned int _level;
            float _speed;
            float _attackCooldown;

            Animation _animation;
            // sf Objects in AEntity ?
            sf::IntRect _hitbox;
            sf::IntRect _attackHitbox;
            sf::IntRect _feetHitbox;
        private:
    };
}

#endif /* !AENTITY_HPP_ */
