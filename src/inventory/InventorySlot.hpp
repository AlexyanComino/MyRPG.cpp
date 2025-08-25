
#ifndef INVENTORYSLOT_HPP_
#define INVENTORYSLOT_HPP_

#include <memory>

#include "Item.hpp"

namespace MyRpg {
    class InventorySlot {
        public:
            InventorySlot();
            ~InventorySlot() = default;

            bool isEmpty() const { return _item == nullptr; }
            bool isHighlighted() const { return _highlighted; }
            bool isSelected() const { return _selected; }
            bool isClicked() const { return _clicked; }

            void setItem(std::unique_ptr<Item> item);
            std::unique_ptr<Item> takeItem();
            Item* getItem() const { return _item.get(); }

            void setPosition(const sf::Vector2f& position);
            void setScreenPosition(const sf::Vector2f& position);
            void setHighlighted(bool highlighted) { _highlighted = highlighted; }
            void setSelected(bool selected) { _selected = selected; }
            void setClicked(bool clicked) { _clicked = clicked; }

            void update(const sf::Vector2f& mousePos, bool clicked, bool hasSelected, const sf::Vector2f& position);
            void display(sf::RenderWindow& window);

        private:
            std::unique_ptr<Item> _item;
            sf::RectangleShape _background;
            sf::RectangleShape _highlight;
            sf::Vector2f _position;
            sf::Vector2f _size;
            bool _highlighted;
            bool _selected;
            bool _clicked;

            void updateColors();
    };
}

#endif /* !INVENTORYSLOT_HPP_ */
