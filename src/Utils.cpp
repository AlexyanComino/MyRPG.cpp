
#include "Utils.hpp"

namespace MyRpg {

    void MyClock::update()
    {
        _time = _clock.getElapsedTime();
        _seconds = static_cast<float>(_time.asMicroseconds() / 1000000.0);
    }

    Animation::Animation(const std::string& texturePath, const int width, const int height)
    {
        if (!_texture.loadFromFile(texturePath))
            throw std::runtime_error("Failed to load texture from " + texturePath);
        _sprite.setTexture(_texture, true);
        this->rect = sf::IntRect(0, 0, width, height);

        _sprite.setTextureRect(this->rect);
        _sprite.setOrigin(sf::Vector2f(static_cast<float>(width) / 2.0f, static_cast<float>(height) / 2.0f));

        _clock = MyClock();
    }

    void Animation::animateLine(int offset, int width, float time)
    {
        if (_clock.getSeconds() > time) {
            if (this->rect.left >= offset)
                this->rect.left = 0;
            else
                this->rect.left += width;
            _sprite.setTextureRect(this->rect);
            _clock.restart();
        }
    }
}