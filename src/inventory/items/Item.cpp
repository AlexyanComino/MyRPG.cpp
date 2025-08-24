
#include "Item.hpp"

namespace MyRpg {

    // Item Implementation
    Item::Item(const std::string& name, const std::string& description,
               itemType type, const std::string& texturePath, rarity rarity)
        : _name(name), _description(description), _type(type), _rarity(rarity)
    {
        setTexture(texturePath);
        // _sprite.setScale(0.5f, 0.5f);
        _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
    }

    void Item::setTexture(const std::string& texturePath)
    {
        if (_texture.loadFromFile(texturePath)) {
            _sprite.setTexture(_texture);
        } else {
            std::cerr << "Failed to load texture: " << texturePath << std::endl;
        }
    }
}
