
#ifndef PAUSEMENU_HPP_
#define PAUSEMENU_HPP_

#include "Menu.hpp"

namespace MyRpg {
    class PauseMenu : public Menu {
        public:
            PauseMenu();
            ~PauseMenu() = default;

            void update(const sf::Vector2f& mousePos, bool mousePressed, bool mouseReleased, const sf::Vector2f& position) override;
            void display(sf::RenderWindow& window) override;

            void setCallbacks(const std::vector<std::function<void()>> callbacks) override;

        private:
            sf::Text _title;
            sf::RectangleShape _background;
            std::function<void()> _resumeGameCallback;
            std::function<void()> _saveGameCallback;
            std::function<void()> _backToMenuCallback;

            void initializeButtons();
    };
}

#endif /* !PAUSEMENU_HPP_ */
