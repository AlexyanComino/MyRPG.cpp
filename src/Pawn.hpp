#ifndef PAWN_HPP_
#define PAWN_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include "AEntity.hpp"
#include "Utils.hpp"

namespace MyRpg {
    typedef enum pawnJob {
        CUT,
        WORKING,
        CARRY,
        EMOTE,
        NO_JOB,
    } pawnJob;

    typedef enum itemPawnType {
        WOOD,
        MEAT,
        GOLD,
        NO_ITEM,
    } itemPawnType;

    struct ItemPawn {
        std::string name;
        itemPawnType type;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f pos;
        int quantity;
    };

    struct Carry {
        sf::Vector2f objPos;
        bool isCarrying;
        itemPawnType itemType;
        std::unique_ptr<ItemPawn> item;
        
        Carry() : isCarrying(false), itemType(NO_ITEM), item(nullptr) {}
    };

    class Pawn : public AEntity {
    public:
        Pawn(const std::string& name, entityColor color, entityFaction faction,
            float initX, float initY, float scale, unsigned int max_health,
            int health, unsigned int attack, unsigned int defense, float speed,
            unsigned int xp, unsigned int level, float attackCooldown);
            
        ~Pawn() = default;

        void update() override;
        void display(sf::RenderWindow& window) override;
        
        const sf::IntRect getHitbox() const override;
        const sf::IntRect getAttackHitbox() const override;
        const sf::IntRect getFeetHitbox() const override;
        const sf::IntRect getNewFeetHitbox(const float x, const float y) const override;

        // Pawn-specific methods
        void setJob(pawnJob job) { _job = job; }
        pawnJob getJob() const { return _job; }
        void setJobPosition(sf::Vector2f pos) { _jobPos = pos; }
        sf::Vector2f getJobPosition() const { return _jobPos; }

    protected:
        const std::string getTexturePathFromColor(const entityColor color) const;
        void updateAnimation();
        void updateJob();

    private:
        sf::RectangleShape _hitboxShape;
        sf::RectangleShape _attackHitboxShape;
        sf::RectangleShape _feetHitboxShape;
        
        // Pawn-specific attributes
        pawnJob _job;
        sf::Vector2f _jobPos;
        sf::Clock _jobClock;
        float _jobCooldown;
        sideX _jobSide;
        std::unique_ptr<Carry> _carry;
    };
}

#endif /* !PAWN_HPP_ */