
#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include "Item.hpp"

namespace MyRpg {
    class Weapon : public Item {
        public:
            Weapon(const std::string& name, const std::string& description,
                const std::string& texturePath, const rarity rarity, const int damage);
            ~Weapon() = default;

            const int getDamage() const { return _damage; }
            const bool isEquiped() const { return _isEquiped; };

        private:
            int _damage;
            bool _isEquiped;
    };
}

#endif /* !WEAPON_HPP_ */
