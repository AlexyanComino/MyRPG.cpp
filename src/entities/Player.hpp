
#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <SFML/Graphics.hpp>
#include <cmath>

#include "AEntity.hpp"

namespace MyRpg {
    template<typename T>
    class Player : public T {
    public:
        Player(const std::string& name, entityColor color, entityFaction faction,
            float initX, float initY, float scale, unsigned int max_health,
            int health, unsigned int attack, unsigned int defense, float speed,
            unsigned int xp, unsigned int level, float attackCooldown) :
            T(name, color, faction, initX, initY, scale, max_health,
              health, attack, defense, speed, xp, level, attackCooldown), firstAttack(true) {}
        ~Player() = default;

        void updateState()
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                if (this->isAttacking() && this->_attackState > 2)
                    this->_maxLineAttack = 1;
                else if (!this->isAttacking()) {
                    this->_state = ST_ATT;
                    this->_lineAttack = 0;
                    this->_maxLineAttack = 0;
                    this->_firstAttack = true;
                    this->_animation.rect.left = 0;
                }
                return;
            }

            if (this->isAttacking())
                return;
            bool isWalking = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                this->_state = (isWalking) ? WALK : RUN;
            else
                this->_state = IDLE;
        };

        float getNewX(float dt)
        {
            float speed = (this->_state == WALK) ? this->_speed / 2 : this->_speed;
            float newX = this->_x;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                speed /= sqrt(2.0f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
                this->_sideX = LEFT;
                newX -= speed * dt;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                this->_sideX = RIGHT;
                newX += speed * dt;
            }

            return newX;
        };

        float getNewY(float dt)
        {
            float speed = (this->_state == WALK) ? this->_speed / 2 : this->_speed;
            float newY = this->_y;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                this->_sideY = NONE;
                return newY;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                speed /= sqrt(2.0f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
                this->_sideY = UP;
                newY -= speed * dt;
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                this->_sideY = DOWN;
                newY += speed * dt;
            } else
                this->_sideY = NONE;

            return newY;
        };

        void updatePos(float dt, Collisions collisionsMap, std::vector<std::unique_ptr<IEntity>>& entities)
        {
            float newX = getNewX(dt);
            float newY = getNewY(dt);

            if (!collisionsMap.isIntRectColliding(this->getNewFeetHitbox(newX, this->_y), this, entities))
                this->_x = newX;
            if (!collisionsMap.isIntRectColliding(this->getNewFeetHitbox(this->_x, newY), this, entities))
                this->_y = newY;
        };

        void handleEvents(float dt, Collisions collisionsMap, std::vector<std::unique_ptr<IEntity>>& entities)
        {
            this->updateState();

            if (!this->isAttacking())
                this->updatePos(dt, collisionsMap, entities);
        };

        private:
            bool firstAttack;
    };
}

#endif /* !PLAYER_HPP_ */
