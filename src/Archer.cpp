#include "Archer.hpp"
#include <cmath>

namespace MyRpg {
    
    Archer::Archer(const std::string& name, entityColor color, entityFaction faction,
            float initX, float initY, float scale, unsigned int max_health,
            int health, unsigned int attack, unsigned int defense, float speed,
            unsigned int xp, unsigned int level, float attackCooldown)
            : AEntity(name, ARCHER, color, faction, IDLE, initX, initY, scale, max_health,
                health, attack, defense, speed, xp, level, attackCooldown, 
                getTexturePathFromColor(color), ARCHER_WIDTH, ARCHER_WIDTH),
                      _hitboxShape(sf::RectangleShape()), _attackHitboxShape(sf::RectangleShape()),
                      _feetHitboxShape(sf::RectangleShape()),
                      _shootCooldown(2.0f), _lastArrowDirection(RIGHT_ARROW)
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
        _hitboxShape.setSize(sf::Vector2f(ARCHER_WIDTH / 3 * _scale, ARCHER_WIDTH / 3 * _scale));
        _attackHitboxShape.setSize(sf::Vector2f(MIN_ARCHER_LENGTH, MIN_ARCHER_LENGTH));
        _feetHitboxShape.setSize(sf::Vector2f(ARCHER_WIDTH / 3 * _scale, 2 * (ARCHER_WIDTH / 3 * _scale) / 4));
    }

    const std::string Archer::getTexturePathFromColor(const entityColor color) const
    {
        switch (color) {
            case BLUE: return "assets/entities/archer/archer_blue.png";
            case PURPLE: return "assets/entities/archer/archer_purple.png";
            case RED: return "assets/entities/archer/archer_red.png";
            case YELLOW: return "assets/entities/archer/archer_yellow.png";
            case BLACK: return "assets/entities/archer/archer_black.png";
            default: return "assets/entities/archer/archer_blue.png";
        }
    }

    void Archer::update()
    {
        updateAnimation();
        updateArrows();
        updateSpriteScale();
        
        // Update hitbox positions
        _hitboxShape.setPosition(_x + ARCHER_WIDTH / 3 * _scale, _y + ARCHER_WIDTH / 6 * _scale);
        _feetHitboxShape.setPosition(_x + ARCHER_WIDTH / 3 * _scale, _y + ARCHER_WIDTH / 2 * _scale);
    }

    void Archer::updateAnimation()
    {
        // Animation logic for archer
        int frameWidth = ARCHER_WIDTH;
        int frameHeight = ARCHER_WIDTH;
        int maxFrames = 7; // Assuming 7 frames for archer (including attack frames)
        
        static sf::Clock animClock;
        static int currentFrame = 0;
        
        if (animClock.getElapsedTime().asSeconds() > 0.1f) { // 10 FPS animation
            currentFrame = (currentFrame + 1) % maxFrames;
            animClock.restart();
        }
        
        // Set texture rect based on state and side
        int stateRow = static_cast<int>(_state);
        int sideOffset = (_sideX == LEFT) ? 1 : 0;
        
        _animation.getSprite().setTextureRect(sf::IntRect(
            currentFrame * frameWidth,
            (stateRow * 2 + sideOffset) * frameHeight,
            frameWidth,
            frameHeight
        ));
    }

    void Archer::shootArrow(sf::Vector2f target)
    {
        if (_shootCooldownClock.getElapsedTime().asSeconds() < _shootCooldown)
            return;

        auto arrow = std::make_unique<Arrow>();
        arrow->position = sf::Vector2f(_x + ARCHER_WIDTH / 2 * _scale, _y + ARCHER_WIDTH / 2 * _scale);
        
        // Calculate direction to target
        sf::Vector2f direction = target - arrow->position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0) {
            direction.x /= length;
            direction.y /= length;
        }
        arrow->direction = direction;
        arrow->target = target;
        arrow->dir = getArrowDirection(direction);
        
        // Load arrow texture (simplified)
        if (!arrow->texture.loadFromFile("assets/entities/archer/arrow.png")) {
            // Handle texture loading error or create a simple colored rectangle
            arrow->sprite.setColor(sf::Color::Yellow);
        }
        arrow->sprite.setTexture(arrow->texture);
        arrow->sprite.setPosition(arrow->position);
        
        _arrows.push_back(std::move(arrow));
        _shootCooldownClock.restart();
        
        // Set archer to attack state
        _state = ATTACK;
    }

    void Archer::updateArrows()
    {
        auto it = _arrows.begin();
        while (it != _arrows.end()) {
            Arrow& arrow = **it;
            
            if (arrow.state == FLY_ARROW) {
                // Move arrow
                float dt = arrow.clock.getElapsedTime().asSeconds();
                arrow.position += arrow.direction * arrow.speed * dt;
                arrow.sprite.setPosition(arrow.position);
                arrow.clock.restart();
                
                // Check if arrow reached target or went too far
                sf::Vector2f toTarget = arrow.target - arrow.position;
                float distToTarget = std::sqrt(toTarget.x * toTarget.x + toTarget.y * toTarget.y);
                
                if (distToTarget < 10.0f) { // Close enough to target
                    arrow.state = HIT_ARROW;
                    // Arrow will be removed next update
                }
                
                // Remove arrow if it's gone too far
                sf::Vector2f origin(_x, _y);
                sf::Vector2f toArrow = arrow.position - origin;
                float distFromOrigin = std::sqrt(toArrow.x * toArrow.x + toArrow.y * toArrow.y);
                
                if (distFromOrigin > 1000.0f) { // Remove if too far
                    it = _arrows.erase(it);
                    continue;
                }
            } else if (arrow.state == HIT_ARROW) {
                // Remove hit arrows after a short delay
                if (arrow.clock.getElapsedTime().asSeconds() > 0.2f) {
                    it = _arrows.erase(it);
                    continue;
                }
            }
            
            ++it;
        }
    }

    arrowDirection Archer::getArrowDirection(sf::Vector2f direction) const
    {
        float angle = std::atan2(direction.y, direction.x) * 180.0f / M_PI;
        if (angle < 0) angle += 360.0f;
        
        if (angle >= 337.5f || angle < 22.5f) return RIGHT_ARROW;
        if (angle >= 22.5f && angle < 67.5f) return DOWN_RIGHT_ARROW;
        if (angle >= 67.5f && angle < 112.5f) return DOWN_ARROW;
        if (angle >= 112.5f && angle < 157.5f) return DOWN_LEFT_ARROW;
        if (angle >= 157.5f && angle < 202.5f) return LEFT_ARROW;
        if (angle >= 202.5f && angle < 247.5f) return UP_LEFT_ARROW;
        if (angle >= 247.5f && angle < 292.5f) return UP_ARROW;
        return UP_RIGHT_ARROW; // 292.5f to 337.5f
    }

    void Archer::display(sf::RenderWindow& window)
    {
        window.draw(_animation.getSprite());
        
        // Draw arrows
        for (const auto& arrow : _arrows) {
            window.draw(arrow->sprite);
        }
        
        // Debug: Draw hitboxes if needed
        // window.draw(_hitboxShape);
        // window.draw(_feetHitboxShape);
        // window.draw(_attackHitboxShape);
    }

    const sf::IntRect Archer::getHitbox() const
    {
        return sf::IntRect(
            _x + ARCHER_WIDTH / 3 * _scale,
            _y + ARCHER_WIDTH / 6 * _scale,
            ARCHER_WIDTH / 3 * _scale,
            ARCHER_WIDTH / 3 * _scale
        );
    }

    const sf::IntRect Archer::getAttackHitbox() const
    {
        // Archer has ranged attack, so this represents the shooting range
        return sf::IntRect(
            _x - MIN_ARCHER_LENGTH / 2,
            _y - MIN_ARCHER_LENGTH / 2,
            MIN_ARCHER_LENGTH,
            MIN_ARCHER_LENGTH
        );
    }

    const sf::IntRect Archer::getFeetHitbox() const
    {
        return sf::IntRect(
            _x + ARCHER_WIDTH / 3 * _scale,
            _y + ARCHER_WIDTH / 2 * _scale,
            ARCHER_WIDTH / 3 * _scale,
            2 * (ARCHER_WIDTH / 3 * _scale) / 4
        );
    }

    const sf::IntRect Archer::getNewFeetHitbox(const float x, const float y) const
    {
        return sf::IntRect(
            x + ARCHER_WIDTH / 3 * _scale,
            y + ARCHER_WIDTH / 2 * _scale,
            ARCHER_WIDTH / 3 * _scale,
            2 * (ARCHER_WIDTH / 3 * _scale) / 4
        );
    }
}