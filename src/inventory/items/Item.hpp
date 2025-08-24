
#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

namespace MyRpg {

    typedef enum itemType {
        WEAPON,
        ARMOR,
        POTION,
        QUEST,
        KEY,
        OTHER,
        ALL
    } itemType;

    typedef enum armorType {
        HELMET,
        CHESTPLATE,
        BOOTS
    } armorType;

    typedef enum rarity {
        COMMON,
        UNCOMMON,
        RARE,
        EPIC,
        LEGENDARY,
    } rarity;

    class Item {
    public:
        Item(const std::string& name, const std::string& description,
             itemType type, const std::string& texturePath, rarity rarity = COMMON);
        virtual ~Item() = default;

        const std::string& getName() const { return _name; }
        const std::string& getDescription() const { return _description; }
        itemType getType() const { return _type; }
        rarity getRarity() const { return _rarity; }
        sf::Sprite& getSprite() { return _sprite; }
        const sf::Sprite& getSprite() const { return _sprite; }

        void setTexture(const std::string& texturePath);

    protected:
        std::string _name;
        std::string _description;
        itemType _type;
        rarity _rarity;
        sf::Texture _texture;
        sf::Sprite _sprite;
    };
};

#endif /* !ITEM_HPP_ */
