#ifndef TORCH_HPP_
#define TORCH_HPP_

#include <SFML/Graphics.hpp>
#include "AEntity.hpp"
#include "Utils.hpp"

namespace MyRpg {
    class Torch : public AEntity {
    public:
        Torch(const std::string& name, entityColor color, entityFaction faction,
            float initX, float initY, float scale, unsigned int max_health,
            int health, unsigned int attack, unsigned int defense, float speed,
            unsigned int xp, unsigned int level, float attackCooldown);
            
        ~Torch() = default;

        void update() override;
        void display(sf::RenderWindow& window) override;
        
        const sf::IntRect getHitbox() const override;
        const sf::IntRect getAttackHitbox() const override;
        const sf::IntRect getFeetHitbox() const override;
        const sf::IntRect getNewFeetHitbox(const float x, const float y) const override;

        // Torch-specific methods
        void lightUp();
        void extinguish();
        bool isLit() const { return _isLit; }

    protected:
        const std::string getTexturePathFromColor(const entityColor color) const;
        void updateAnimation();
        void updateFlame();

    private:
        sf::RectangleShape _hitboxShape;
        sf::RectangleShape _attackHitboxShape;
        sf::RectangleShape _feetHitboxShape;
        
        // Torch-specific attributes
        bool _isLit;
        sf::Sprite _flameSprite;
        sf::Texture _flameTexture;
        sf::Clock _flameClock;
        int _flameFrame;
    };
}

#endif /* !TORCH_HPP_ */