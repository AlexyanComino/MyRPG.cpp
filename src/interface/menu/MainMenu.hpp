
#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include "Menu.hpp"

namespace MyRpg {
    class MainMenu : public Menu {
    public:
        MainMenu();
        ~MainMenu() = default;

        void update(const sf::Vector2f& mousePos, bool mousePressed, bool mouseReleased, const sf::Vector2f& position) override;
        void display(sf::RenderWindow& window) override;

        void setCallbacks(const std::vector<std::function<void()>> callbacks) override;

    private:
        sf::Text _title;
        std::function<void()> _startGameCallback;
        std::function<void()> _openSettingsCallback;
        std::function<void()> _quitCallback;

        void initializeButtons();
    };
}

#endif /* !MAINMENU_HPP_ */
