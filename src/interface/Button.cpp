
#include "Button.hpp"
#include <iostream>

namespace MyRpg {

    // Button Implementation
    Button::Button(const std::string& text, const sf::Vector2f& position,
                   const sf::Vector2f& size, const std::string& fontPath,
                   const int fontSize, const sf::Color& textColor,
                   const sf::Color& normalColor, const sf::Color& hoverColor,
                   const sf::Color& clickColor, const sf::Color& outlineColor,
                   const float outlineThickness, std::function<void()> callback)
        : _position(position), _size(size), _state(NOTHING),
          _normalColor(normalColor), _hoverColor(hoverColor),
          _clickColor(clickColor), _callback(callback)
    {
        if (!_font.loadFromFile(fontPath)) {
            std::cerr << "Warning: Could not load font: " << fontPath << std::endl;
        }

        _text.setFont(_font);
        _text.setString(text);
        _text.setCharacterSize(fontSize);
        _text.setFillColor(textColor);
        _text.setOrigin(_text.getGlobalBounds().width / 2, _text.getGlobalBounds().height);

        _background.setSize(_size);
        _background.setFillColor(_normalColor);
        _background.setOutlineColor(outlineColor);
        _background.setOutlineThickness(outlineThickness);
        _background.setOrigin(_background.getGlobalBounds().width / 2, _background.getGlobalBounds().height / 2);

        setPosition(position);
    }

    void Button::update(const sf::Vector2f mousePos, bool mousePressed, bool mouseReleased, const sf::Vector2f position)
    {
        sf::FloatRect bounds = _background.getGlobalBounds();
        bool mouseInBounds = bounds.contains(mousePos);

        if (mousePressed && mouseInBounds) {
            _state = CLICKED;
            if (_callback) {
                _callback();
            }
        } else if (mouseReleased && _state == CLICKED && mouseInBounds) {
            _state = RELEASED;
        } else if (mouseInBounds) {
            _state = HOVERED;
        } else {
            _state = NOTHING;
        }

        updateColors();

        setPosition(_position + position);
    }

    void Button::display(sf::RenderWindow& window)
    {
        window.draw(_background);
        window.draw(_text);
    }

    void Button::setPosition(sf::Vector2f position)
    {
        _background.setPosition(position);
        _text.setPosition(position);
    }

    void Button::setSize(sf::Vector2f size)
    {
        _size = size;
        _background.setSize(_size);
        setPosition(_position);
    }

    void Button::setText(const std::string& text)
    {
        _text.setString(text);
        setPosition(_position);
    }

    void Button::updateColors()
    {
        switch (_state) {
            case CLICKED:
                _background.setFillColor(_clickColor);
                break;
            case HOVERED:
                _background.setFillColor(_hoverColor);
                break;
            default:
                _background.setFillColor(_normalColor);
                break;
        }
    }
}
