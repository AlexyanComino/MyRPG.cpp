
#include "Weapon.hpp"

namespace MyRpg {
    Weapon::Weapon(const std::string& name, const std::string& description,
                const std::string& texturePath, const rarity rarity, const int damage)
        : Item(name, description, WEAPON, texturePath, rarity), _damage(damage), _isEquiped(false)
    {
    }
}
