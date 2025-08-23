
#include "AEntity.hpp"

namespace MyRpg {
    void AEntity::updateSpriteScale()
    {
        sf::Vector2f scale = _animation.getSprite().getScale();

        if (_sideX == RIGHT && scale.x != _scale)
            _animation.setSpriteScale(sf::Vector2f(_scale, _scale));
        if (_sideX == LEFT && scale.x != -_scale)
            _animation.setSpriteScale(sf::Vector2f(-_scale, _scale));
    }
}
