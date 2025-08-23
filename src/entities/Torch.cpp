#include "Torch.hpp"

namespace MyRpg {

    Torch::Torch(const std::string& name, entityColor color, entityFaction faction,
            float initX, float initY, float scale, unsigned int max_health,
            int health, unsigned int attack, unsigned int defense, float speed,
            unsigned int xp, unsigned int level, float attackCooldown)
            : AEntity(name, TORCH, color, faction, IDLE, initX, initY, scale, max_health,
                health, attack, defense, speed, xp, level, attackCooldown,
                getTexturePathFromColor(color), TORCH_WIDTH, TORCH_WIDTH),
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
        _hitboxShape.setSize(sf::Vector2f(TORCH_WIDTH / 3 * _scale, TORCH_WIDTH / 3 * _scale));
        _attackHitboxShape.setSize(sf::Vector2f(MIN_TORCH_LENGTH, MIN_TORCH_LENGTH));
        _feetHitboxShape.setSize(sf::Vector2f(TORCH_WIDTH / 3 * _scale, 2 * (TORCH_WIDTH / 3 * _scale) / 4));
    }

    const std::string Torch::getTexturePathFromColor(const entityColor color) const
    {
        switch (color) {
            case BLUE: return "assets/entities/torch/Torch_Blue.png";
            case PURPLE: return "assets/entities/torch/Torch_Purple.png";
            case RED: return "assets/entities/torch/Torch_Red.png";
            case YELLOW: return "assets/entities/torch/Torch_Yellow.png";
            case BLACK: return "assets/entities/torch/Torch_Black.png";
            default: return "assets/entities/torch/Torch_Blue.png";
        }
    }

    void Torch::update()
    {
        sf::Vector2f currentPos(_x, _y);
        if (_animation.getSprite().getPosition() != currentPos)
            _animation.setSpritePosition(currentPos);

        _animation.updateClock();

        updateSpriteScale();

        if (_state == IDLE || _state == INTERACT) {
            _animation.rect.top = 0;
            _animation.animateLine(TORCH_OFFSET, TORCH_WIDTH, 0.1f);
        }
        if (_state == WALK || _state == RUN) {
            _animation.rect.top = WARRIOR_WIDTH;
            _animation.animateLine(TORCH_OFFSET, TORCH_WIDTH, 0.1f);
        }
        if (isAttacking()) {
            if (_firstAttack) {
                int multiplier = (_sideY == UP) ? 4 : (_sideY == DOWN) ? 3 : 2;
                _animation.rect.top = TORCH_WIDTH * multiplier;
                _firstAttack = false;
            }
            _maxLineAttack = 0;
            _animation.animateWarriorAttack(_lineAttack, _attackState, _maxLineAttack, _state);
        }
    }

    void Torch::display(sf::RenderWindow& window)
    {
        window.draw(_animation.getSprite());

        if (true)
            displayHitboxes(window);
    }

    void Torch::displayHitboxes(sf::RenderWindow& window)
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

    const sf::IntRect Torch::getHitbox() const
    {
        return sf::IntRect(
            static_cast<int>(_x - TORCH_WIDTH / 6 * _scale),
            static_cast<int>(_y - TORCH_WIDTH / 7 * _scale),
            static_cast<int>(TORCH_WIDTH / 5.0f * _scale),
            static_cast<int>(TORCH_WIDTH / 3.5f * _scale)
        );
    }

    const sf::IntRect Torch::getAttackHitbox() const
    {
        // Implement with combat system
        return sf::IntRect();
    }

    const sf::IntRect Torch::getFeetHitbox() const
    {
        return sf::IntRect(
             static_cast<int>(_x - TORCH_WIDTH / 6 * _scale),
             static_cast<int>((_y + TORCH_WIDTH / 7 * _scale) - (2 * (TORCH_WIDTH / 5.0f * _scale) / 5) / 2),
             static_cast<int>(TORCH_WIDTH / 5.0f * _scale),
             static_cast<int>(2 * (TORCH_WIDTH / 5.0f * _scale) / 5)
        );
    }

    const sf::IntRect Torch::getNewFeetHitbox(const float x, const float y) const
    {
        return sf::IntRect(
             static_cast<int>(x - TORCH_WIDTH / 6 * _scale),
             static_cast<int>((y + TORCH_WIDTH / 7 * _scale) - (2 * (TORCH_WIDTH / 5.0f * _scale) / 5) / 2),
             static_cast<int>(TORCH_WIDTH / 5.0f * _scale),
             static_cast<int>(2 * (TORCH_WIDTH / 5.0f * _scale) / 5)
        );
    }
}
