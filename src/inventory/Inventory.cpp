
#include "Inventory.hpp"

namespace MyRpg {
    Inventory::Inventory() : _isOpen(false), _gold(0), _selectedItem(nullptr)
    {
        _slots.reserve(TOTAL_SLOTS);
        for (int i = 0; i < TOTAL_SLOTS; ++i) {
            _slots.push_back(std::make_unique<InventorySlot>());
        }

        initializeUI();

        // Arrange slots in a grid
        float startX = -520.0f;
        float startY = -70.0f;
        float slotSize = 70.0f;

        for (int i = 0; i < TOTAL_SLOTS; ++i) {
            int row = i / INVENTORY_COLS;
            int col = i % INVENTORY_COLS;
            sf::Vector2f position(startX + col * slotSize, startY + row * slotSize);
            _slots[i]->setScreenPosition(position);
        }
    }

    void Inventory::initializeUI()
    {
        // Load font
        if (!_font.loadFromFile("assets/fonts/m6x11plus.ttf")) {
            std::cerr << "Warning: Could not load inventory font" << std::endl;
        }

        // Background
        _backgroundPosition = sf::Vector2f(-200.0f, 30.0f);

        _background.setSize(sf::Vector2f(800.0f, 600.0f));
        _background.setFillColor(sf::Color(30, 30, 30, 220));
        _background.setOutlineColor(sf::Color::White);
        _background.setOutlineThickness(3.0f);
        _background.setOrigin(_background.getGlobalBounds().width / 2, _background.getGlobalBounds().height / 2);
        _background.setPosition(_backgroundPosition);

        // Title
        _titleTextPosition = sf::Vector2f(-570.0f, -270.0f);
        _titleText.setFont(_font);
        _titleText.setString("Inventory");
        _titleText.setCharacterSize(36);
        _titleText.setFillColor(sf::Color::White);
        _titleText.setPosition(_titleTextPosition);

        // Gold text
        _goldTextPosition = sf::Vector2f(-560.0f, -220.0f);

        _goldText.setFont(_font);
        _goldText.setCharacterSize(24);
        _goldText.setFillColor(sf::Color::Yellow);
        _goldText.setPosition(_goldTextPosition);
        updateGoldDisplay();

        // Description area
        _descriptionBackgroundPosition = sf::Vector2f(350.0f, -170.0f);

        _descriptionBackground.setSize(sf::Vector2f(250.0f, 200.0f));
        _descriptionBackground.setFillColor(sf::Color(20, 20, 20, 200));
        _descriptionBackground.setOutlineColor(sf::Color(128, 128, 128));
        _descriptionBackground.setOutlineThickness(2.0f);
        _descriptionBackground.setOrigin(_descriptionBackground.getGlobalBounds().width / 2, _descriptionBackground.getGlobalBounds().height / 2);
        _descriptionBackground.setPosition(_descriptionBackgroundPosition);

        _descriptionTextPosistion = sf::Vector2f(230.0f, -260.0f);
        _descriptionText.setFont(_font);
        _descriptionText.setCharacterSize(24);
        _descriptionText.setFillColor(sf::Color::White);
        _descriptionText.setPosition(_descriptionTextPosistion);
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

    void Inventory::update(const sf::Vector2f& mousePos, bool clicked, const sf::Vector2f& position)
    {
        if (!_isOpen)
            return;

        _selectedItem = nullptr;

        for (auto& slot : _slots) {
            slot->update(mousePos, clicked, position);
            if (slot->isSelected() && slot->getItem()) {
                _selectedItem = slot->getItem();
            }
        }

        updateDescription(position);

        _background.setPosition(position + _backgroundPosition);
        _titleText.setPosition(position + _titleTextPosition);
        _goldText.setPosition(position + _goldTextPosition);
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

    void Inventory::updateDescription(const sf::Vector2f& position)
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
        } else if (auto armor = dynamic_cast<Armor*>(_selectedItem)) {
            description += "Defense: " + std::to_string(armor->getDefense()) + "\n";
            description += "Speed: " + std::to_string(armor->getSpeedModifier());
        } else if (auto potion = dynamic_cast<Potion*>(_selectedItem)) {
            description += "Heal Amount: " + std::to_string(potion->getHealAmount());
        }

        _descriptionText.setString(description);

        _descriptionBackground.setPosition(position + _descriptionBackgroundPosition);
        _descriptionText.setPosition(position + _descriptionTextPosistion);
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
}
