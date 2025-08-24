
#include "PlayerStatus.hpp"

namespace MyRpg {
    PlayerStatus::PlayerStatus()
    {
        initializeSlots();
    }

    void PlayerStatus::equipWeapon(std::unique_ptr<Weapon> weapon)
    {
        _equippedWeapon = std::move(weapon);
    }

    void PlayerStatus::equipArmor(std::unique_ptr<Armor> armor)
    {
        switch (armor->getArmorType()) {
            case HELMET:
                _equippedHelmet = std::move(armor);
                break;
            case CHESTPLATE:
                _equippedChestplate = std::move(armor);
                break;
            case BOOTS:
                _equippedBoots = std::move(armor);
                break;
        }
    }

    void PlayerStatus::unequipWeapon()
    {
        _equippedWeapon.reset();
    }

    void PlayerStatus::unequipArmor(armorType type)
    {
        switch (type) {
            case HELMET:
                _equippedHelmet.reset();
                break;
            case CHESTPLATE:
                _equippedChestplate.reset();
                break;
            case BOOTS:
                _equippedBoots.reset();
                break;
        }
    }

    Armor* PlayerStatus::getEquippedArmor(armorType type) const
    {
        switch (type) {
            case HELMET:
                return _equippedHelmet.get();
            case CHESTPLATE:
                return _equippedChestplate.get();
            case BOOTS:
                return _equippedBoots.get();
        }
        return nullptr;
    }

    int PlayerStatus::getTotalAttack() const
    {
        int attack = 10; // Base attack
        if (_equippedWeapon) {
            attack += _equippedWeapon->getDamage();
        }
        return attack;
    }

    int PlayerStatus::getTotalDefense() const
    {
        int defense = 0;
        if (_equippedHelmet) defense += _equippedHelmet->getDefense();
        if (_equippedChestplate) defense += _equippedChestplate->getDefense();
        if (_equippedBoots) defense += _equippedBoots->getDefense();
        return defense;
    }

    float PlayerStatus::getTotalSpeed() const
    {
        float speed = 100.0f; // Base speed
        if (_equippedHelmet) speed += _equippedHelmet->getSpeedModifier();
        if (_equippedChestplate) speed += _equippedChestplate->getSpeedModifier();
        if (_equippedBoots) speed += _equippedBoots->getSpeedModifier();
        return speed;
    }

    void PlayerStatus::initializeSlots()
    {
        sf::Vector2f slotSize(64.0f, 64.0f);
        sf::Color slotColor(60, 60, 60, 200);

        _weaponSlot.setSize(slotSize);
        _weaponSlot.setFillColor(slotColor);
        _weaponSlot.setOutlineColor(sf::Color::White);
        _weaponSlot.setOutlineThickness(2.0f);
        _weaponSlot.setPosition(950.0f, 200.0f);

        _helmetSlot.setSize(slotSize);
        _helmetSlot.setFillColor(slotColor);
        _helmetSlot.setOutlineColor(sf::Color::White);
        _helmetSlot.setOutlineThickness(2.0f);
        _helmetSlot.setPosition(950.0f, 280.0f);

        _chestplateSlot.setSize(slotSize);
        _chestplateSlot.setFillColor(slotColor);
        _chestplateSlot.setOutlineColor(sf::Color::White);
        _chestplateSlot.setOutlineThickness(2.0f);
        _chestplateSlot.setPosition(950.0f, 360.0f);

        _bootsSlot.setSize(slotSize);
        _bootsSlot.setFillColor(slotColor);
        _bootsSlot.setOutlineColor(sf::Color::White);
        _bootsSlot.setOutlineThickness(2.0f);
        _bootsSlot.setPosition(950.0f, 440.0f);
    }

    void PlayerStatus::display(sf::RenderWindow& window)
    {
        window.draw(_weaponSlot);
        window.draw(_helmetSlot);
        window.draw(_chestplateSlot);
        window.draw(_bootsSlot);

        if (_equippedWeapon) {
            _equippedWeapon->getSprite().setPosition(_weaponSlot.getPosition());
            window.draw(_equippedWeapon->getSprite());
        }

        if (_equippedHelmet) {
            _equippedHelmet->getSprite().setPosition(_helmetSlot.getPosition());
            window.draw(_equippedHelmet->getSprite());
        }

        if (_equippedChestplate) {
            _equippedChestplate->getSprite().setPosition(_chestplateSlot.getPosition());
            window.draw(_equippedChestplate->getSprite());
        }

        if (_equippedBoots) {
            _equippedBoots->getSprite().setPosition(_bootsSlot.getPosition());
            window.draw(_equippedBoots->getSprite());
        }
    }
}
