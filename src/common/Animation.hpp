
#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_

#include "constants.hpp"
#include "IEntity.hpp"
#include "Clock.hpp"

#include <string>
#include <SFML/Graphics.hpp>

namespace MyRpg {
    class Animation {
        public:
            Animation(const std::string& _texturePath, const int width, const int height);
            ~Animation() = default;

            void updateClock() { _clock.update(); };
            void animateLine(int offset, int width, float time);
            void resetWarriorAttack(int& lineAttack, int& attackState, int& maxLineAttack, entityState& state);
            void animateWarriorAttack(int& lineAttack, int& attackState, int& maxLineAttack, entityState& state);

            const sf::Sprite& getSprite() const { return _sprite; };


            void setSpritePosition(const sf::Vector2f position) { _sprite.setPosition(position); };
            void setSpriteScale(const sf::Vector2f scale) { _sprite.setScale(scale); };

            sf::IntRect rect;
        private:
            sf::Texture _texture;
            sf::Sprite _sprite;
            Clock _clock;
    };
}

#endif /* !ANIMATION_HPP_ */
