
#include "InventorySlot.hpp"

namespace MyRpg {
    InventorySlot::InventorySlot()
        : _item(nullptr), _size(64.0f, 64.0f), _highlighted(false), _selected(false)
    {
        _background.setSize(_size);
        _background.setFillColor(sf::Color(50, 50, 50, 200));
        _background.setOutlineColor(sf::Color::White);
        _background.setOutlineThickness(1.0f);
        _background.setOrigin(_background.getGlobalBounds().width / 2, _background.getGlobalBounds().height / 2);

        _highlight.setSize(_size);
        _highlight.setFillColor(sf::Color(255, 255, 0, 100));
        _highlight.setOutlineColor(sf::Color::Yellow);
        _highlight.setOutlineThickness(2.0f);
        _highlight.setOrigin(_highlight.getGlobalBounds().width / 2, _highlight.getGlobalBounds().height / 2);
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

    void InventorySlot::setPosition(const sf::Vector2f& position)
    {
        _background.setPosition(_position + position);
        _highlight.setPosition(_position + position);
        if (_item) {
            _item->getSprite().setPosition(_position + position);
        }
    }

    void InventorySlot::setScreenPosition(const sf::Vector2f& position)
    {
        _position = position;
    }

    void InventorySlot::update(const sf::Vector2f& mousePos, bool clicked, bool hasSelected, const sf::Vector2f& position)
    {
        sf::FloatRect bounds = _background.getGlobalBounds();
        _highlighted = bounds.contains(mousePos);

        if (_highlighted && clicked && !hasSelected) {
            _selected = !_selected;
        }

        setPosition(position);
    }

    void InventorySlot::display(sf::RenderWindow& window)
    {
        window.draw(_background);

        if (_highlighted) {
            window.draw(_highlight);
        }

        if (_item && !_selected) {
            window.draw(_item->getSprite());
        }
    }
}
