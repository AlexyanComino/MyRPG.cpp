
#ifndef WARRIOR_HPP_
#define WARRIOR_HPP_

#include "AEntity.hpp"
#include "constants.hpp"

namespace MyRpg {
    class Warrior : public AEntity {
        public:
            Warrior(const std::string& name, entityColor color, entityFaction faction,
                    float initX, float initY, float scale, unsigned int max_health,
                    int health, unsigned int attack, unsigned int defense, float speed,
                    unsigned int xp, unsigned int level, float attackCooldown);
            ~Warrior() = default;

            void update();
            void display(sf::RenderWindow& window);

            void displayHitboxes(sf::RenderWindow& window);

            void attack(float dt) override;

            const sf::IntRect getHitbox() const override;
            const sf::IntRect getFeetHitbox() const override;
            const sf::IntRect getAttackHitbox() const override;

            const sf::IntRect getNewFeetHitbox(const float x, const float y) const override;

        protected:
            int _lineAttack;
            int _maxLineAttack;

            int _attackState;

            bool _firstAttack;

            sf::RectangleShape _hitboxShape;
            sf::RectangleShape _attackHitboxShape;
            sf::RectangleShape _feetHitboxShape;

        private:
            const std::string getTexturePathFromColor(const entityColor color) const;
    };
}

#endif /* !WARRIOR_HPP_ */
