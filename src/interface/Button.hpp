
#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace MyRpg {

    typedef enum buttonState {
        HOVERED,
        CLICKED,
        RELEASED,
        NOTHING
    } buttonState;

    class Button {
        public:
            Button(const std::string& text, const sf::Vector2f& position,
                   const sf::Vector2f& size, const std::string& fontPath = "assets/fonts/m6x11plus.ttf",
                   const int fontSize = 24, const sf::Color& textColor = sf::Color::White,
                   const sf::Color& normalColor = sf::Color::Blue, const sf::Color& hoverColor = sf::Color::Cyan,
                   const sf::Color& clickColor = sf::Color::Green, const sf::Color& outlineColor = sf::Color::White,
                   const float outlineThickness = 2.0f, std::function<void()> callback = nullptr);
            ~Button() = default;

            void update(const sf::Vector2f mousePos, bool mousePressed, bool mouseReleased, const sf::Vector2f position);
            void display(sf::RenderWindow& window);

            void setCallback(std::function<void()> callback) { _callback = callback; }
            buttonState getState() const { return _state; }
            bool isClicked() const { return _state == CLICKED; }
            bool isHovered() const { return _state == HOVERED; }

            void setPosition(sf::Vector2f position);
            void setSize(sf::Vector2f size);
            void setText(const std::string& text);

        private:
            sf::Text _text;
            sf::Font _font;
            sf::RectangleShape _background;
            sf::Vector2f _position;
            sf::Vector2f _size;
            buttonState _state;
            sf::Color _normalColor;
            sf::Color _hoverColor;
            sf::Color _clickColor;
            std::function<void()> _callback;

        void updateColors();
    };
}

#endif /* !BUTTON_HPP_ */
