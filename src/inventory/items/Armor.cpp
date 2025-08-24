
#include "Armor.hpp"

namespace MyRpg {
    Armor::Armor(const std::string& name, const std::string& description,
                 const std::string& texturePath, const rarity rarity,
                 armorType armorType, int defense, int speedModifier)
        : Item(name, description, ARMOR, texturePath, rarity), _armorType(armorType),
          _defense(defense), _speedModifier(speedModifier), _isEquiped(false)
    {
    }
}
