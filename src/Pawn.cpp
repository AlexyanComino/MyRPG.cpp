#include "Pawn.hpp"

namespace MyRpg {
    
    Pawn::Pawn(const std::string& name, entityColor color, entityFaction faction,
            float initX, float initY, float scale, unsigned int max_health,
            int health, unsigned int attack, unsigned int defense, float speed,
            unsigned int xp, unsigned int level, float attackCooldown)
            : AEntity(name, PAWN, color, faction, IDLE, initX, initY, scale, max_health,
                health, attack, defense, speed, xp, level, attackCooldown, 
                getTexturePathFromColor(color), PAWN_WIDTH, PAWN_WIDTH),
                      _hitboxShape(sf::RectangleShape()), _attackHitboxShape(sf::RectangleShape()),
                      _feetHitboxShape(sf::RectangleShape()),
                      _job(NO_JOB), _jobPos(0.0f, 0.0f), _jobCooldown(0.0f), _jobSide(RIGHT),
                      _carry(std::make_unique<Carry>())
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
        _hitboxShape.setSize(sf::Vector2f(PAWN_WIDTH / 3 * _scale, PAWN_WIDTH / 3 * _scale));
        _attackHitboxShape.setSize(sf::Vector2f(10.0f, 10.0f)); // Implement with combat
        _feetHitboxShape.setSize(sf::Vector2f(PAWN_WIDTH / 3 * _scale, 2 * (PAWN_WIDTH / 3 * _scale) / 4));
    }

    const std::string Pawn::getTexturePathFromColor(const entityColor color) const
    {
        switch (color) {
            case BLUE: return "assets/entities/pawn/pawn_blue.png";
            case PURPLE: return "assets/entities/pawn/pawn_purple.png";
            case RED: return "assets/entities/pawn/pawn_red.png";
            case YELLOW: return "assets/entities/pawn/pawn_yellow.png";
            case BLACK: return "assets/entities/pawn/pawn_black.png";
            default: return "assets/entities/pawn/pawn_blue.png";
        }
    }

    void Pawn::update()
    {
        updateAnimation();
        updateJob();
        updateSpriteScale();
        
        // Update hitbox positions
        _hitboxShape.setPosition(_x + PAWN_WIDTH / 3 * _scale, _y + PAWN_WIDTH / 6 * _scale);
        _feetHitboxShape.setPosition(_x + PAWN_WIDTH / 3 * _scale, _y + PAWN_WIDTH / 2 * _scale);
    }

    void Pawn::updateAnimation()
    {
        // Simple animation logic - cycle through sprite frames based on state
        int frameWidth = PAWN_WIDTH;
        int frameHeight = PAWN_WIDTH;
        int maxFrames = 6; // Assuming 6 frames per animation row
        
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

    void Pawn::updateJob()
    {
        if (_job == NO_JOB)
            return;
            
        // Simple job logic - in a full implementation this would be more complex
        if (_jobClock.getElapsedTime().asSeconds() > _jobCooldown) {
            // Reset job cooldown
            _jobCooldown = 2.0f + (float)rand() / RAND_MAX * 2.0f; // Random between 2-4 seconds
            _jobClock.restart();
            
            // Update state based on job
            switch (_job) {
                case WORKING:
                    _state = WORK;
                    break;
                case CUT:
                    _state = WORK;
                    break;
                case CARRY:
                    _state = (_carry && _carry->isCarrying) ? MOVE_CARRY : IDLE_CARRY;
                    break;
                case EMOTE:
                    _state = INTERACT;
                    break;
                default:
                    _state = IDLE;
                    break;
            }
        }
    }

    void Pawn::display(sf::RenderWindow& window)
    {
        window.draw(_animation.getSprite());
        
        // Debug: Draw hitboxes if needed
        // window.draw(_hitboxShape);
        // window.draw(_feetHitboxShape);
        // window.draw(_attackHitboxShape);
    }

    const sf::IntRect Pawn::getHitbox() const
    {
        return sf::IntRect(
            _x + PAWN_WIDTH / 3 * _scale,
            _y + PAWN_WIDTH / 6 * _scale,
            PAWN_WIDTH / 3 * _scale,
            PAWN_WIDTH / 3 * _scale
        );
    }

    const sf::IntRect Pawn::getAttackHitbox() const
    {
        // Simple attack hitbox - in front of the entity
        float offsetX = (_sideX == RIGHT) ? PAWN_WIDTH * _scale : -PAWN_WIDTH / 3 * _scale;
        return sf::IntRect(
            _x + offsetX,
            _y + PAWN_WIDTH / 3 * _scale,
            PAWN_WIDTH / 3 * _scale,
            PAWN_WIDTH / 3 * _scale
        );
    }

    const sf::IntRect Pawn::getFeetHitbox() const
    {
        return sf::IntRect(
            _x + PAWN_WIDTH / 3 * _scale,
            _y + PAWN_WIDTH / 2 * _scale,
            PAWN_WIDTH / 3 * _scale,
            2 * (PAWN_WIDTH / 3 * _scale) / 4
        );
    }

    const sf::IntRect Pawn::getNewFeetHitbox(const float x, const float y) const
    {
        return sf::IntRect(
            x + PAWN_WIDTH / 3 * _scale,
            y + PAWN_WIDTH / 2 * _scale,
            PAWN_WIDTH / 3 * _scale,
            2 * (PAWN_WIDTH / 3 * _scale) / 4
        );
    }
}