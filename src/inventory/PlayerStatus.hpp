
#ifndef PLAYERSTATUS_HPP_
#define PLAYERSTATUS_HPP_

#include <memory>

#include "Armor.hpp"
#include "Weapon.hpp"

namespace MyRpg {
    class PlayerStatus {
        public:
            PlayerStatus();
            ~PlayerStatus() = default;

            // Equipment slots
            void equipWeapon(std::unique_ptr<Weapon> weapon);
            void equipArmor(std::unique_ptr<Armor> armor);
            void unequipWeapon();
            void unequipArmor(armorType type);

            Weapon* getEquippedWeapon() const { return _equippedWeapon.get(); }
            Armor* getEquippedArmor(armorType type) const;

            // Stats calculation including equipment bonuses
            int getTotalAttack() const;
            int getTotalDefense() const;
            float getTotalSpeed() const;

            void display(sf::RenderWindow& window);

        private:
            std::unique_ptr<Weapon> _equippedWeapon;
            std::unique_ptr<Armor> _equippedHelmet;
            std::unique_ptr<Armor> _equippedChestplate;
            std::unique_ptr<Armor> _equippedBoots;

            // UI elements for equipment display
            sf::RectangleShape _weaponSlot;
            sf::RectangleShape _helmetSlot;
            sf::RectangleShape _chestplateSlot;
            sf::RectangleShape _bootsSlot;

            void initializeSlots();
    };
}

#endif /* !PLAYERSTATUS_HPP_ */
