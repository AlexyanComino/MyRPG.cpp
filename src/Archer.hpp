#ifndef ARCHER_HPP_
#define ARCHER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "AEntity.hpp"
#include "Utils.hpp"

namespace MyRpg {
    typedef enum arrowDirection {
        UP_ARROW,
        UP_LEFT_ARROW,
        UP_RIGHT_ARROW,
        DOWN_ARROW,
        DOWN_LEFT_ARROW,
        DOWN_RIGHT_ARROW,
        LEFT_ARROW,
        RIGHT_ARROW,
    } arrowDirection;

    typedef enum arrowState {
        FLY_ARROW,
        HIT_ARROW,
    } arrowState;

    struct Arrow {
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position;
        sf::Vector2f direction;
        sf::Vector2f target;
        arrowState state;
        sf::Clock clock;
        arrowDirection dir;
        float speed;
        
        Arrow() : state(FLY_ARROW), speed(500.0f) {}
    };

    class Archer : public AEntity {
    public:
        Archer(const std::string& name, entityColor color, entityFaction faction,
            float initX, float initY, float scale, unsigned int max_health,
            int health, unsigned int attack, unsigned int defense, float speed,
            unsigned int xp, unsigned int level, float attackCooldown);
            
        ~Archer() = default;

        void update() override;
        void display(sf::RenderWindow& window) override;
        
        const sf::IntRect getHitbox() const override;
        const sf::IntRect getAttackHitbox() const override;
        const sf::IntRect getFeetHitbox() const override;
        const sf::IntRect getNewFeetHitbox(const float x, const float y) const override;

        // Archer-specific methods
        void shootArrow(sf::Vector2f target);
        void updateArrows();
        std::vector<std::unique_ptr<Arrow>>& getArrows() { return _arrows; }

    protected:
        const std::string getTexturePathFromColor(const entityColor color) const;
        void updateAnimation();
        arrowDirection getArrowDirection(sf::Vector2f direction) const;

    private:
        sf::RectangleShape _hitboxShape;
        sf::RectangleShape _attackHitboxShape;
        sf::RectangleShape _feetHitboxShape;
        
        // Archer-specific attributes
        std::vector<std::unique_ptr<Arrow>> _arrows;
        sf::Clock _shootCooldownClock;
        float _shootCooldown;
        arrowDirection _lastArrowDirection;
    };
}

#endif /* !ARCHER_HPP_ */