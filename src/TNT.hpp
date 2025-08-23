#ifndef TNT_HPP_
#define TNT_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "AEntity.hpp"
#include "Utils.hpp"

namespace MyRpg {
    struct Dynamite {
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position;
        sf::Vector2f velocity;
        sf::Vector2f target;
        bool isLaunched;
        float angle;
        sf::Clock clock;
        
        Dynamite() : isLaunched(false), angle(0.0f) {}
    };

    struct Explosion {
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f center;
        sf::CircleShape blastRadius;
        int radius;
        sf::Clock animationClock;
        int currentFrame;
        bool isActive;
        
        Explosion() : radius(100), currentFrame(0), isActive(false) {}
    };

    class TNT : public AEntity {
    public:
        TNT(const std::string& name, entityColor color, entityFaction faction,
            float initX, float initY, float scale, unsigned int max_health,
            int health, unsigned int attack, unsigned int defense, float speed,
            unsigned int xp, unsigned int level, float attackCooldown);
            
        ~TNT() = default;

        void update() override;
        void display(sf::RenderWindow& window) override;
        
        const sf::IntRect getHitbox() const override;
        const sf::IntRect getAttackHitbox() const override;
        const sf::IntRect getFeetHitbox() const override;
        const sf::IntRect getNewFeetHitbox(const float x, const float y) const override;

        // TNT-specific methods
        void throwDynamite(sf::Vector2f target);
        void explode(sf::Vector2f center);
        bool isDynamiteLaunched() const { return _dynamite && _dynamite->isLaunched; }
        bool isExploded() const { return _explosion && _explosion->isActive; }

    protected:
        const std::string getTexturePathFromColor(const entityColor color) const;
        void updateAnimation();
        void updateDynamite();
        void updateExplosion();

    private:
        sf::RectangleShape _hitboxShape;
        sf::RectangleShape _attackHitboxShape;
        sf::RectangleShape _feetHitboxShape;
        
        // TNT-specific attributes
        std::unique_ptr<Dynamite> _dynamite;
        std::unique_ptr<Explosion> _explosion;
        sf::Clock _throwCooldownClock;
        float _throwCooldown;
        sf::Sprite _targetSprite; // Visual indicator for target
        sf::Texture _targetTexture;
    };
}

#endif /* !TNT_HPP_ */