
#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_

#include <memory>

#include "InventorySlot.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"
#include "Potion.hpp"

namespace MyRpg {
    class Inventory {
        public:
            static const int INVENTORY_ROWS = 6;
            static const int INVENTORY_COLS = 8;
            static const int TOTAL_SLOTS = INVENTORY_ROWS * INVENTORY_COLS;

            Inventory();
            ~Inventory() = default;

            bool addItem(std::unique_ptr<Item> item);
            std::unique_ptr<Item> removeItem(int slotIndex);

            void addGold(int amount) { _gold += amount; }
            bool removeGold(int amount);
            int getGold() const { return _gold; }

            InventorySlot& getSlot(int index) { return *_slots[index]; }
            const InventorySlot& getSlot(int index) const { return *_slots[index]; }

            bool isOpen() const { return _isOpen; }
            void open() { _isOpen = true; }
            void close() { _isOpen = false; }
            void toggle() { _isOpen = !_isOpen; }

            void update(const sf::Vector2f& mousePos, bool clicked, bool released, const sf::Vector2f& position);
            void display(sf::RenderWindow& window);

            // Find item by name or type
            Item* findItem(const std::string& name) const;
            std::vector<Item*> findItemsByType(itemType type) const;

        private:
            std::vector<std::unique_ptr<InventorySlot>> _slots;
            bool _isOpen;
            int _gold;

            // UI Elements
            sf::RectangleShape _background;
            sf::Vector2f _backgroundPosition;
            sf::Text _titleText;
            sf::Vector2f _titleTextPosition;
            sf::Text _goldText;
            sf::Vector2f _goldTextPosition;
            sf::Font _font;

            // Selected item for description
            Item* _selectedItem;
            InventorySlot* _selectedSlot;
            sf::RectangleShape _descriptionBackground;
            sf::Vector2f _descriptionBackgroundPosition;
            sf::Text _descriptionText;
            sf::Vector2f _descriptionTextPosistion;

            void initializeUI();
            void updateGoldDisplay();
            void updateDescription(const sf::Vector2f& position);
            int findEmptySlot() const;

            void switchItems(InventorySlot* slot1, InventorySlot* slot2);
            void resetSelected();
    };
}

#endif /* !INVENTORY_HPP_ */
