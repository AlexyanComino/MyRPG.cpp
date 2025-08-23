
#include "Warrior.hpp"

#include <iostream>

namespace MyRpg {

    Warrior::Warrior(const std::string& name, entityColor color, entityFaction faction,
            float initX, float initY, float scale, unsigned int max_health,
            int health, unsigned int attack, unsigned int defense, float speed,
            unsigned int xp, unsigned int level, float attackCooldown)
            : AEntity(name, WARRIOR, color, faction, IDLE, initX, initY, scale, max_health,
                health, attack, defense, speed, xp, level, attackCooldown,
                getTexturePathFromColor(color), WARRIOR_WIDTH, WARRIOR_WIDTH),
                    _hitboxShape(sf::RectangleShape()), _attackHitboxShape(sf::RectangleShape()),
                    _feetHitboxShape(sf::RectangleShape()), _lineAttack(0), _maxLineAttack(0),
                    _attackState(0), _firstAttack(true)

    {
        _hitboxShape.setFillColor(sf::Color::Transparent);
        _attackHitboxShape.setFillColor(sf::Color::Transparent);
        _feetHitboxShape.setFillColor(sf::Color::Transparent);
        _hitboxShape.setOutlineColor(sf::Color::Black);
        _attackHitboxShape.setOutlineColor(sf::Color::Red);
        _feetHitboxShape.setOutlineColor(sf::Color::Blue);
        _hitboxShape.setOutlineThickness(2);
        _attackHitboxShape.setOutlineThickness(2);
        _feetHitboxShape.setOutlineThickness(2);
        _hitboxShape.setSize(sf::Vector2f(WARRIOR_WIDTH / 3 * _scale, WARRIOR_WIDTH / 3 * _scale));
        _attackHitboxShape.setSize(sf::Vector2f(10.0f, 10.0f)); // Implement with combat
        _feetHitboxShape.setSize(sf::Vector2f(WARRIOR_WIDTH / 3 * _scale, 2 * (WARRIOR_WIDTH / 3 * _scale) / 4));
    }

    const std::string Warrior::getTexturePathFromColor(const entityColor color) const
    {
        switch (color) {
            case BLUE: return "assets/entities/warrior/Warrior_Blue.png";
            case PURPLE: return "assets/entities/warrior/Warrior_Purple.png";
            case RED: return "assets/entities/warrior/Warrior_Red.png";
            case YELLOW: return "assets/entities/warrior/Warrior_Yellow.png";
            case BLACK: return "assets/entities/warrior/Warrior_Black.png";
            default: return "assets/entities/warrior/Warrior_Blue.png";
        }
    }

    void Warrior::update()
    {
        sf::Vector2f currentPos(_x, _y);
        if (_animation.getSprite().getPosition() != currentPos)
            _animation.setSpritePosition(currentPos);

        _animation.updateClock();

        updateSpriteScale();

        if (_state == IDLE || _state == INTERACT) {
            _animation.rect.top = 0;
            _animation.animateLine(WARRIOR_OFFSET, WARRIOR_WIDTH, 0.1f);
        }
        if (_state == WALK || _state == RUN) {
            _animation.rect.top = WARRIOR_WIDTH;
            _animation.animateLine(WARRIOR_OFFSET, WARRIOR_WIDTH, 0.1f);
        }
        if (isAttacking()) {
            if (_firstAttack) {
                int multiplier = (_sideY == UP) ? 6 : (_sideY == DOWN) ? 4 : 2;
                _animation.rect.top = WARRIOR_WIDTH * multiplier;
                _firstAttack = false;
            }
            _animation.animateWarriorAttack(_lineAttack, _attackState, _maxLineAttack, _state);
        }
    }

    void Warrior::display(sf::RenderWindow& window)
    {
        window.draw(_animation.getSprite());
        if (true)
            displayHitboxes(window);
    }

    void Warrior::displayHitboxes(sf::RenderWindow& window)
    {
        sf::IntRect hitbox = getHitbox();
        sf::IntRect feetHitbox = getFeetHitbox();
        sf::IntRect attackHitbox = getAttackHitbox();

        _hitboxShape.setPosition(sf::Vector2f(static_cast<float>(hitbox.left), static_cast<float>(hitbox.top)));
        _feetHitboxShape.setPosition(sf::Vector2f(static_cast<float>(feetHitbox.left), static_cast<float>(feetHitbox.top)));
        _attackHitboxShape.setPosition(sf::Vector2f(static_cast<float>(attackHitbox.left), static_cast<float>(attackHitbox.top)));
        window.draw(_hitboxShape);
        window.draw(_feetHitboxShape);
        // window.draw(_attackHitboxShape);
    }

    void Warrior::attack(float dt)
    {

    }

    const sf::IntRect Warrior::getHitbox() const
    {
        return sf::IntRect(
            static_cast<int>(_x - WARRIOR_WIDTH / 6 * _scale),
            static_cast<int>(_y - WARRIOR_WIDTH / 6 * _scale),
            static_cast<int>(WARRIOR_WIDTH / 3 * _scale),
            static_cast<int>(WARRIOR_WIDTH / 3 * _scale)
        );
    }

    const sf::IntRect Warrior::getAttackHitbox() const
    {
        return sf::IntRect(); // Implement when doing combat system
    }

    const sf::IntRect Warrior::getFeetHitbox() const
    {
        return sf::IntRect(
            static_cast<int>(_x - WARRIOR_WIDTH / 6 * _scale),
            static_cast<int>(_y + WARRIOR_WIDTH / 6 * _scale - (2 * (WARRIOR_WIDTH / 3 * _scale) / 4) / 2),
            static_cast<int>(WARRIOR_WIDTH / 3 * _scale),
            static_cast<int>(2 * (WARRIOR_WIDTH / 3 * _scale) / 4)
        );
    }

    const sf::IntRect Warrior::getNewFeetHitbox(const float x, const float y) const
    {
        return sf::IntRect(
            static_cast<int>(x - WARRIOR_WIDTH / 6 * _scale),
            static_cast<int>(y + WARRIOR_WIDTH / 6 * _scale - (2 * (WARRIOR_WIDTH / 3 * _scale) / 4) / 2),
            static_cast<int>(WARRIOR_WIDTH / 3 * _scale),
            static_cast<int>(2 * (WARRIOR_WIDTH / 3 * _scale) / 4)
        );
    }
}
