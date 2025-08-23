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
                      _feetHitboxShape(sf::RectangleShape()),
                      _isLit(true), _flameFrame(0)
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
        
        // Load flame texture
        if (!_flameTexture.loadFromFile("assets/entities/torch/flame.png")) {
            // Handle error or use a fallback
        }
        _flameSprite.setTexture(_flameTexture);
    }

    const std::string Torch::getTexturePathFromColor(const entityColor color) const
    {
        switch (color) {
            case BLUE: return "assets/entities/torch/torch_blue.png";
            case PURPLE: return "assets/entities/torch/torch_purple.png";
            case RED: return "assets/entities/torch/torch_red.png";
            case YELLOW: return "assets/entities/torch/torch_yellow.png";
            case BLACK: return "assets/entities/torch/torch_black.png";
            default: return "assets/entities/torch/torch_blue.png";
        }
    }

    void Torch::update()
    {
        updateAnimation();
        if (_isLit) {
            updateFlame();
        }
        updateSpriteScale();
        
        // Update hitbox positions
        _hitboxShape.setPosition(_x + TORCH_WIDTH / 3 * _scale, _y + TORCH_WIDTH / 6 * _scale);
        _feetHitboxShape.setPosition(_x + TORCH_WIDTH / 3 * _scale, _y + TORCH_WIDTH / 2 * _scale);
    }

    void Torch::updateAnimation()
    {
        // Torch animation - different frames for lit/unlit state
        int frameWidth = TORCH_WIDTH;
        int frameHeight = TORCH_WIDTH;
        int maxFrames = _isLit ? 6 : 1; // Animated when lit, static when not
        
        static sf::Clock animClock;
        static int currentFrame = 0;
        
        if (_isLit && animClock.getElapsedTime().asSeconds() > 0.15f) { // Slower animation for torch
            currentFrame = (currentFrame + 1) % maxFrames;
            animClock.restart();
        }
        
        // Set texture rect
        int stateRow = _isLit ? 0 : 1; // Different row for lit/unlit
        int sideOffset = (_sideX == LEFT) ? 1 : 0;
        
        _animation.getSprite().setTextureRect(sf::IntRect(
            currentFrame * frameWidth,
            (stateRow * 2 + sideOffset) * frameHeight,
            frameWidth,
            frameHeight
        ));
    }

    void Torch::updateFlame()
    {
        if (!_isLit) return;
        
        // Animate flame sprite
        int flameFrameWidth = 64; // Assuming flame sprite frame width
        int flameFrameHeight = 64;
        int maxFlameFrames = 6;
        
        if (_flameClock.getElapsedTime().asSeconds() > 0.1f) {
            _flameFrame = (_flameFrame + 1) % maxFlameFrames;
            _flameClock.restart();
        }
        
        _flameSprite.setTextureRect(sf::IntRect(
            _flameFrame * flameFrameWidth,
            0,
            flameFrameWidth,
            flameFrameHeight
        ));
        
        // Position flame above torch
        _flameSprite.setPosition(
            _x + (TORCH_WIDTH * _scale - flameFrameWidth) / 2,
            _y - flameFrameHeight / 2
        );
    }

    void Torch::lightUp()
    {
        _isLit = true;
        _state = IDLE; // Reset to idle when lit
    }

    void Torch::extinguish()
    {
        _isLit = false;
        _state = DEAD; // Use dead state for extinguished torch
    }

    void Torch::display(sf::RenderWindow& window)
    {
        window.draw(_animation.getSprite());
        
        // Draw flame if lit
        if (_isLit) {
            window.draw(_flameSprite);
        }
        
        // Debug: Draw hitboxes if needed
        // window.draw(_hitboxShape);
        // window.draw(_feetHitboxShape);
        // window.draw(_attackHitboxShape);
    }

    const sf::IntRect Torch::getHitbox() const
    {
        return sf::IntRect(
            _x + TORCH_WIDTH / 3 * _scale,
            _y + TORCH_WIDTH / 6 * _scale,
            TORCH_WIDTH / 3 * _scale,
            TORCH_WIDTH / 3 * _scale
        );
    }

    const sf::IntRect Torch::getAttackHitbox() const
    {
        // Torch has fire damage in a small area around it
        return sf::IntRect(
            _x - MIN_TORCH_LENGTH / 4,
            _y - MIN_TORCH_LENGTH / 4,
            MIN_TORCH_LENGTH / 2,
            MIN_TORCH_LENGTH / 2
        );
    }

    const sf::IntRect Torch::getFeetHitbox() const
    {
        return sf::IntRect(
            _x + TORCH_WIDTH / 3 * _scale,
            _y + TORCH_WIDTH / 2 * _scale,
            TORCH_WIDTH / 3 * _scale,
            2 * (TORCH_WIDTH / 3 * _scale) / 4
        );
    }

    const sf::IntRect Torch::getNewFeetHitbox(const float x, const float y) const
    {
        return sf::IntRect(
            x + TORCH_WIDTH / 3 * _scale,
            y + TORCH_WIDTH / 2 * _scale,
            TORCH_WIDTH / 3 * _scale,
            2 * (TORCH_WIDTH / 3 * _scale) / 4
        );
    }
}