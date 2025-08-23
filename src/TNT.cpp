#include "TNT.hpp"
#include <cmath>

namespace MyRpg {
    
    TNT::TNT(const std::string& name, entityColor color, entityFaction faction,
            float initX, float initY, float scale, unsigned int max_health,
            int health, unsigned int attack, unsigned int defense, float speed,
            unsigned int xp, unsigned int level, float attackCooldown)
            : AEntity(name, entityType::TNT, color, faction, IDLE, initX, initY, scale, max_health,
                health, attack, defense, speed, xp, level, attackCooldown, 
                getTexturePathFromColor(color), TNT_WIDTH, TNT_WIDTH),
                      _hitboxShape(sf::RectangleShape()), _attackHitboxShape(sf::RectangleShape()),
                      _feetHitboxShape(sf::RectangleShape()),
                      _throwCooldown(3.0f)
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
        _hitboxShape.setSize(sf::Vector2f(TNT_WIDTH / 3 * _scale, TNT_WIDTH / 3 * _scale));
        _attackHitboxShape.setSize(sf::Vector2f(MIN_TNT_LENGTH, MIN_TNT_LENGTH));
        _feetHitboxShape.setSize(sf::Vector2f(TNT_WIDTH / 3 * _scale, 2 * (TNT_WIDTH / 3 * _scale) / 4));
        
        // Initialize dynamite and explosion objects
        _dynamite = std::make_unique<Dynamite>();
        _explosion = std::make_unique<Explosion>();
        
        // Load textures
        if (!_dynamite->texture.loadFromFile("assets/entities/tnt/dynamite.png")) {
            // Handle error or use fallback
        }
        _dynamite->sprite.setTexture(_dynamite->texture);
        
        if (!_explosion->texture.loadFromFile("assets/entities/tnt/explosion.png")) {
            // Handle error or use fallback
        }
        _explosion->sprite.setTexture(_explosion->texture);
        
        if (!_targetTexture.loadFromFile("assets/entities/tnt/target.png")) {
            // Handle error or use fallback
        }
        _targetSprite.setTexture(_targetTexture);
        
        // Set up explosion circle
        _explosion->blastRadius.setFillColor(sf::Color::Transparent);
        _explosion->blastRadius.setOutlineColor(sf::Color(255, 100, 0, 100)); // Orange with transparency
        _explosion->blastRadius.setOutlineThickness(3);
        _explosion->blastRadius.setRadius(_explosion->radius);
    }

    const std::string TNT::getTexturePathFromColor(const entityColor color) const
    {
        switch (color) {
            case BLUE: return "assets/entities/tnt/tnt_blue.png";
            case PURPLE: return "assets/entities/tnt/tnt_purple.png";
            case RED: return "assets/entities/tnt/tnt_red.png";
            case YELLOW: return "assets/entities/tnt/tnt_yellow.png";
            case BLACK: return "assets/entities/tnt/tnt_black.png";
            default: return "assets/entities/tnt/tnt_blue.png";
        }
    }

    void TNT::update()
    {
        updateAnimation();
        updateDynamite();
        updateExplosion();
        updateSpriteScale();
        
        // Update hitbox positions
        _hitboxShape.setPosition(_x + TNT_WIDTH / 3 * _scale, _y + TNT_WIDTH / 6 * _scale);
        _feetHitboxShape.setPosition(_x + TNT_WIDTH / 3 * _scale, _y + TNT_WIDTH / 2 * _scale);
    }

    void TNT::updateAnimation()
    {
        // TNT animation
        int frameWidth = TNT_WIDTH;
        int frameHeight = TNT_WIDTH;
        int maxFrames = 5; // Assuming 5 frames for TNT
        
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

    void TNT::throwDynamite(sf::Vector2f target)
    {
        if (_throwCooldownClock.getElapsedTime().asSeconds() < _throwCooldown)
            return;

        if (_dynamite->isLaunched || _explosion->isActive)
            return;

        _dynamite->position = sf::Vector2f(_x + TNT_WIDTH / 2 * _scale, _y + TNT_WIDTH / 2 * _scale);
        _dynamite->target = target;
        _dynamite->isLaunched = true;
        
        // Calculate trajectory (simplified parabolic motion)
        sf::Vector2f direction = target - _dynamite->position;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        
        // Normalize direction
        if (distance > 0) {
            direction.x /= distance;
            direction.y /= distance;
        }
        
        // Set initial velocity (simplified)
        float throwSpeed = 300.0f;
        _dynamite->velocity = direction * throwSpeed;
        
        _dynamite->sprite.setPosition(_dynamite->position);
        _dynamite->clock.restart();
        
        _throwCooldownClock.restart();
        _state = ATTACK;
    }

    void TNT::updateDynamite()
    {
        if (!_dynamite->isLaunched)
            return;
            
        float dt = _dynamite->clock.getElapsedTime().asSeconds();
        _dynamite->clock.restart();
        
        // Simple physics - move toward target
        sf::Vector2f direction = _dynamite->target - _dynamite->position;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        
        if (distance < 20.0f) {
            // Reached target - explode
            explode(_dynamite->position);
            _dynamite->isLaunched = false;
        } else {
            // Continue moving
            if (distance > 0) {
                direction.x /= distance;
                direction.y /= distance;
            }
            
            _dynamite->position += direction * 200.0f * dt; // Move at constant speed
            _dynamite->sprite.setPosition(_dynamite->position);
            
            // Rotate dynamite as it flies
            _dynamite->angle += 180.0f * dt; // 180 degrees per second
            _dynamite->sprite.setRotation(_dynamite->angle);
        }
    }

    void TNT::explode(sf::Vector2f center)
    {
        _explosion->center = center;
        _explosion->isActive = true;
        _explosion->currentFrame = 0;
        _explosion->animationClock.restart();
        
        // Position explosion sprite and blast radius
        _explosion->sprite.setPosition(center.x - EXPLO_WIDTH / 2, center.y - EXPLO_WIDTH / 2);
        _explosion->blastRadius.setPosition(center.x - _explosion->radius, center.y - _explosion->radius);
    }

    void TNT::updateExplosion()
    {
        if (!_explosion->isActive)
            return;
            
        // Animate explosion
        int frameWidth = EXPLO_WIDTH;
        int frameHeight = EXPLO_WIDTH;
        int maxFrames = 8; // Assuming 8 frames for explosion animation
        
        if (_explosion->animationClock.getElapsedTime().asSeconds() > 0.1f) {
            _explosion->currentFrame++;
            _explosion->animationClock.restart();
            
            if (_explosion->currentFrame >= maxFrames) {
                _explosion->isActive = false;
                _state = IDLE; // Return to idle after explosion
                return;
            }
        }
        
        _explosion->sprite.setTextureRect(sf::IntRect(
            _explosion->currentFrame * frameWidth,
            0,
            frameWidth,
            frameHeight
        ));
    }

    void TNT::display(sf::RenderWindow& window)
    {
        window.draw(_animation.getSprite());
        
        // Draw dynamite if launched
        if (_dynamite->isLaunched) {
            window.draw(_dynamite->sprite);
        }
        
        // Draw explosion if active
        if (_explosion->isActive) {
            window.draw(_explosion->blastRadius); // Draw blast radius first
            window.draw(_explosion->sprite); // Draw explosion animation on top
        }
        
        // Debug: Draw hitboxes if needed
        // window.draw(_hitboxShape);
        // window.draw(_feetHitboxShape);
        // window.draw(_attackHitboxShape);
    }

    const sf::IntRect TNT::getHitbox() const
    {
        return sf::IntRect(
            _x + TNT_WIDTH / 3 * _scale,
            _y + TNT_WIDTH / 6 * _scale,
            TNT_WIDTH / 3 * _scale,
            TNT_WIDTH / 3 * _scale
        );
    }

    const sf::IntRect TNT::getAttackHitbox() const
    {
        // TNT has explosive attack with large range
        return sf::IntRect(
            _x - MIN_TNT_LENGTH / 2,
            _y - MIN_TNT_LENGTH / 2,
            MIN_TNT_LENGTH,
            MIN_TNT_LENGTH
        );
    }

    const sf::IntRect TNT::getFeetHitbox() const
    {
        return sf::IntRect(
            _x + TNT_WIDTH / 3 * _scale,
            _y + TNT_WIDTH / 2 * _scale,
            TNT_WIDTH / 3 * _scale,
            2 * (TNT_WIDTH / 3 * _scale) / 4
        );
    }

    const sf::IntRect TNT::getNewFeetHitbox(const float x, const float y) const
    {
        return sf::IntRect(
            x + TNT_WIDTH / 3 * _scale,
            y + TNT_WIDTH / 2 * _scale,
            TNT_WIDTH / 3 * _scale,
            2 * (TNT_WIDTH / 3 * _scale) / 4
        );
    }
}