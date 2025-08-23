
#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <iostream>

#include "Button.hpp"

namespace MyRpg {
    typedef enum gameState {
        MAIN_MENU,
        GAME,
        PAUSE,
        SETTINGS,
        SAVE_MENU,
        SELECTOR,
        INVENTORY,
        MAP,
        SKILL_TREE,
        LOADING,
        END,
        CREDITS,
    } gameState;

    class Menu {
    public:
        Menu(const std::string& fontPath);
        virtual ~Menu() = default;

        virtual void update(const sf::Vector2f& mousePos, bool mousePressed, bool mouseReleased, const sf::Vector2f& position) = 0;
        virtual void display(sf::RenderWindow& window) = 0;
        virtual void handleEvent(const sf::Event& event) {}
        virtual void setCallbacks(const std::vector<std::function<void()>> callbacks) = 0;

        void addButton(std::unique_ptr<Button> button);

    protected:
        std::vector<std::unique_ptr<Button>> _buttons;
        sf::Font _font;
    };
}

#endif /* !MENU_HPP_ */
