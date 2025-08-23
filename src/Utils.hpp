
#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "IEntity.hpp"

namespace MyRpg {
    class MyClock {
        public:
            MyClock() = default;
            ~MyClock() = default;

            const float getSeconds() const { return _seconds; };

            void update();
            void restart() { _clock.restart(); };

        private:
            sf::Clock _clock;
            sf::Time _time;
            float _seconds;
    };

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
            MyClock _clock;
    };
}

#endif /* !UTILS_HPP_ */
