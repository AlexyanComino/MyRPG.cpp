
#ifndef ARMOR_HPP_
#define ARMOR_HPP_

#include "Item.hpp"

namespace MyRpg {
    class Armor : public Item {
        public:
            Armor(const std::string& name, const std::string& description,
                const std::string& texturePath, const rarity rarity,
                const armorType armorType, const int defense, const int speedModifier = 0);
            ~Armor() = default;

            const armorType getArmorType() const { return _armorType; }
            const int getDefense() const { return _defense; }
            const int getSpeedModifier() const { return _speedModifier; }
            const bool isEquiped() const { return _isEquiped; };

        private:
            armorType _armorType;
            int _defense;
            int _speedModifier;
            bool _isEquiped;
    };
}

#endif /* !ARMOR_HPP_ */
