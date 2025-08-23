#include "Inventory.hpp"
#include <iostream>
#include <algorithm>

namespace MyRpg {

    // Item Implementation
    Item::Item(const std::string& name, const std::string& description, 
               itemType type, rarity rarity)
        : _name(name), _description(description), _type(type), _rarity(rarity)
    {
        // Default sprite setup
        _sprite.setScale(0.5f, 0.5f); // Make items smaller in inventory
    }

    void Item::setTexture(const std::string& texturePath)
    {
        if (_texture.loadFromFile(texturePath)) {
            _sprite.setTexture(_texture);
        } else {
            std::cerr << "Failed to load texture: " << texturePath << std::endl;
        }
    }

    // Weapon Implementation
    Weapon::Weapon(const std::string& name, const std::string& description,
                   int damage, float attackSpeed)
        : Item(name, description, WEAPON), _damage(damage), _attackSpeed(attackSpeed)
    {
    }

    // Armor Implementation
    Armor::Armor(const std::string& name, const std::string& description,
                 armorType armorType, int defense, int speedModifier)
        : Item(name, description, ARMOR), _armorType(armorType), 
          _defense(defense), _speedModifier(speedModifier)
    {
    }

    // Potion Implementation
    Potion::Potion(const std::string& name, const std::string& description,
                   int healAmount)
        : Item(name, description, POTION), _healAmount(healAmount)
    {
    }

    void Potion::use()
    {
        // In a full implementation, this would apply the healing effect
        std::cout << "Used " << _name << " - Healed " << _healAmount << " HP!" << std::endl;
    }

    // InventorySlot Implementation
    InventorySlot::InventorySlot() 
        : _item(nullptr), _size(64.0f, 64.0f), _highlighted(false), _selected(false)
    {
        _background.setSize(_size);
        _background.setFillColor(sf::Color(50, 50, 50, 200));
        _background.setOutlineColor(sf::Color::White);
        _background.setOutlineThickness(1.0f);
        
        _highlight.setSize(_size);
        _highlight.setFillColor(sf::Color(255, 255, 0, 100)); // Yellow highlight
        _highlight.setOutlineColor(sf::Color::Yellow);
        _highlight.setOutlineThickness(2.0f);
    }

    void InventorySlot::setItem(std::unique_ptr<Item> item)
    {
        _item = std::move(item);
        if (_item) {
            _item->getSprite().setPosition(_position);
        }
    }

    std::unique_ptr<Item> InventorySlot::takeItem()
    {
        return std::move(_item);
    }

    void InventorySlot::setPosition(sf::Vector2f position)
    {
        _position = position;
        _background.setPosition(position);
        _highlight.setPosition(position);
        if (_item) {
            _item->getSprite().setPosition(position);
        }
    }

    void InventorySlot::update(sf::Vector2f mousePos, bool clicked)
    {
        sf::FloatRect bounds = _background.getGlobalBounds();
        _highlighted = bounds.contains(mousePos);
        
        if (_highlighted && clicked) {
            _selected = !_selected;
        }
    }

    void InventorySlot::display(sf::RenderWindow& window)
    {
        window.draw(_background);
        
        if (_highlighted || _selected) {
            window.draw(_highlight);
        }
        
        if (_item) {
            window.draw(_item->getSprite());
        }
    }

    // Inventory Implementation
    Inventory::Inventory() : _isOpen(false), _gold(0), _selectedItem(nullptr)
    {
        _slots.reserve(TOTAL_SLOTS);
        for (int i = 0; i < TOTAL_SLOTS; ++i) {
            _slots.push_back(std::make_unique<InventorySlot>());
        }
        
        initializeUI();
        
        // Arrange slots in a grid
        float startX = 200.0f;
        float startY = 150.0f;
        float slotSize = 70.0f;
        
        for (int i = 0; i < TOTAL_SLOTS; ++i) {
            int row = i / INVENTORY_COLS;
            int col = i % INVENTORY_COLS;
            sf::Vector2f position(startX + col * slotSize, startY + row * slotSize);
            _slots[i]->setPosition(position);
        }
    }

    void Inventory::initializeUI()
    {
        // Load font
        if (!_font.loadFromFile("assets/fonts/inventory.ttf")) {
            std::cerr << "Warning: Could not load inventory font" << std::endl;
        }
        
        // Background
        _background.setSize(sf::Vector2f(800.0f, 600.0f));
        _background.setFillColor(sf::Color(30, 30, 30, 220));
        _background.setOutlineColor(sf::Color::White);
        _background.setOutlineThickness(3.0f);
        _background.setPosition(100.0f, 50.0f);
        
        // Title
        _titleText.setFont(_font);
        _titleText.setString("Inventory");
        _titleText.setCharacterSize(36);
        _titleText.setFillColor(sf::Color::White);
        _titleText.setPosition(150.0f, 70.0f);
        
        // Gold text
        _goldText.setFont(_font);
        _goldText.setCharacterSize(24);
        _goldText.setFillColor(sf::Color::Yellow);
        _goldText.setPosition(150.0f, 120.0f);
        updateGoldDisplay();
        
        // Description area
        _descriptionBackground.setSize(sf::Vector2f(250.0f, 200.0f));
        _descriptionBackground.setFillColor(sf::Color(20, 20, 20, 200));
        _descriptionBackground.setOutlineColor(sf::Color(128, 128, 128));
        _descriptionBackground.setOutlineThickness(2.0f);
        _descriptionBackground.setPosition(620.0f, 150.0f);
        
        _descriptionText.setFont(_font);
        _descriptionText.setCharacterSize(16);
        _descriptionText.setFillColor(sf::Color::White);
        _descriptionText.setPosition(630.0f, 160.0f);
    }

    bool Inventory::addItem(std::unique_ptr<Item> item)
    {
        int emptySlot = findEmptySlot();
        if (emptySlot == -1) {
            return false; // Inventory full
        }
        
        _slots[emptySlot]->setItem(std::move(item));
        return true;
    }

    std::unique_ptr<Item> Inventory::removeItem(int slotIndex)
    {
        if (slotIndex < 0 || slotIndex >= TOTAL_SLOTS) {
            return nullptr;
        }
        
        return _slots[slotIndex]->takeItem();
    }

    bool Inventory::removeGold(int amount)
    {
        if (_gold < amount) {
            return false;
        }
        
        _gold -= amount;
        updateGoldDisplay();
        return true;
    }

    void Inventory::update(sf::Vector2f mousePos, bool clicked)
    {
        if (!_isOpen) return;
        
        _selectedItem = nullptr;
        
        for (auto& slot : _slots) {
            slot->update(mousePos, clicked);
            if (slot->isSelected() && slot->getItem()) {
                _selectedItem = slot->getItem();
            }
        }
        
        updateDescription();
    }

    void Inventory::display(sf::RenderWindow& window)
    {
        if (!_isOpen) return;
        
        window.draw(_background);
        window.draw(_titleText);
        window.draw(_goldText);
        
        for (auto& slot : _slots) {
            slot->display(window);
        }
        
        // Draw description area
        window.draw(_descriptionBackground);
        if (_selectedItem) {
            window.draw(_descriptionText);
        }
    }

    Item* Inventory::findItem(const std::string& name) const
    {
        for (const auto& slot : _slots) {
            if (!slot->isEmpty() && slot->getItem()->getName() == name) {
                return slot->getItem();
            }
        }
        return nullptr;
    }

    std::vector<Item*> Inventory::findItemsByType(itemType type) const
    {
        std::vector<Item*> items;
        for (const auto& slot : _slots) {
            if (!slot->isEmpty() && slot->getItem()->getType() == type) {
                items.push_back(slot->getItem());
            }
        }
        return items;
    }

    void Inventory::updateGoldDisplay()
    {
        _goldText.setString("Gold: " + std::to_string(_gold));
    }

    void Inventory::updateDescription()
    {
        if (!_selectedItem) {
            _descriptionText.setString("");
            return;
        }
        
        std::string description = _selectedItem->getName() + "\n\n";
        description += _selectedItem->getDescription() + "\n\n";
        
        // Add type-specific information
        if (auto weapon = dynamic_cast<Weapon*>(_selectedItem)) {
            description += "Damage: " + std::to_string(weapon->getDamage()) + "\n";
            description += "Speed: " + std::to_string(weapon->getAttackSpeed());
        } else if (auto armor = dynamic_cast<Armor*>(_selectedItem)) {
            description += "Defense: " + std::to_string(armor->getDefense()) + "\n";
            description += "Speed Mod: " + std::to_string(armor->getSpeedModifier());
        } else if (auto potion = dynamic_cast<Potion*>(_selectedItem)) {
            description += "Heal Amount: " + std::to_string(potion->getHealAmount());
        }
        
        _descriptionText.setString(description);
    }

    int Inventory::findEmptySlot() const
    {
        for (int i = 0; i < TOTAL_SLOTS; ++i) {
            if (_slots[i]->isEmpty()) {
                return i;
            }
        }
        return -1;
    }

    // PlayerStatus Implementation
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