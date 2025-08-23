
#include "Animation.hpp"

namespace MyRpg {
    Animation::Animation(const std::string& texturePath, const int width, const int height)
    {
        if (!_texture.loadFromFile(texturePath))
            throw std::runtime_error("Failed to load texture from " + texturePath);
        _sprite.setTexture(_texture, true);
        this->rect = sf::IntRect(0, 0, width, height);

        _sprite.setTextureRect(this->rect);
        _sprite.setOrigin(sf::Vector2f(static_cast<float>(width) / 2.0f, static_cast<float>(height) / 2.0f));

        _clock = Clock();
    }

    void Animation::animateLine(int offset, int width, float time)
    {
        if (_clock.getSeconds() <= time)
            return;

        if (this->rect.left >= offset)
            this->rect.left = 0;
        else
            this->rect.left += width;
        _sprite.setTextureRect(this->rect);
        _clock.restart();
    }

    void Animation::resetWarriorAttack(int& lineAttack, int& attackState, int& maxLineAttack, entityState& state)
    {
        state = IDLE;
        this->rect.left = 0;
        this->rect.top = 0;
        lineAttack = 0;
        attackState = 0;
    }

    void Animation::animateWarriorAttack(int& lineAttack, int& attackState, int& maxLineAttack, entityState& state)
    {
        if (_clock.getSeconds() <= 0.1f)
            return;

        if (this->rect.left >= WARRIOR_OFFSET && lineAttack == 0) {
            if (lineAttack < maxLineAttack) {
                lineAttack++;
                this->rect.left = 0;
                this->rect.top += WARRIOR_WIDTH;
                attackState = 0;
                state = ATTACK;
            } else
                resetWarriorAttack(lineAttack, attackState, maxLineAttack, state);
        } else if (this->rect.left >= WARRIOR_OFFSET && lineAttack == 1) {
            resetWarriorAttack(lineAttack, attackState, maxLineAttack, state);
        } else {
            this->rect.left += WARRIOR_WIDTH;
            attackState++;
        }
        _sprite.setTextureRect(this->rect);
        _clock.restart();
    }
}
