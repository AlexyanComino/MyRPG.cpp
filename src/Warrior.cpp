
#include "Warrior.hpp"

namespace MyRpg {

    Warrior::Warrior(const std::string& name, entityColor color, entityFaction faction,
            float initX, float initY, float scale, unsigned int max_health,
            int health, unsigned int attack, unsigned int defense, float speed,
            unsigned int xp, unsigned int level, float attackCooldown)
            : AEntity(name, WARRIOR, color, faction, IDLE, initX, initY, scale, max_health,
                health, attack, defense, speed, xp, level, attackCooldown, 
                getTexturePathFromColor(color), WARRIOR_WIDTH, WARRIOR_WIDTH),
                      _hitboxShape(sf::RectangleShape()), _attackHitboxShape(sf::RectangleShape()),
                      _feetHitboxShape(sf::RectangleShape())

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
        std::vector<std::string> texturePaths = {
            "assets/Entities/Warriors/Warrior_Blue.png",
            "assets/Entities/Warriors/Warrior_Purple.png",
            "assets/Entities/Warriors/Warrior_Red.png",
            "assets/Entities/Warriors/Warrior_Yellow.png",
            "assets/Entities/Warriors/Warrior_Black.png",
        };
        return texturePaths[color];
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
            _animation.animateLine(WARRIOR_OFFSET, WARRIOR_WIDTH, 0.1);
        }
        if (_state == WALK || _state == RUN) {
            _animation.rect.top = WARRIOR_WIDTH;
            _animation.animateLine(WARRIOR_OFFSET, WARRIOR_WIDTH, 0.1);
        }
        // if (isAttacking)
        //      animateAttack()
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
    
        _hitboxShape.setPosition(sf::Vector2f(hitbox.left, hitbox.top));
        _feetHitboxShape.setPosition(sf::Vector2f(feetHitbox.left, feetHitbox.top));
        _attackHitboxShape.setPosition(sf::Vector2f(attackHitbox.left, attackHitbox.top));
        window.draw(_hitboxShape);
        window.draw(_feetHitboxShape);
        // window.draw(_attackHitboxShape);
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