
#ifndef MENUMANAGER_HPP_
#define MENUMANAGER_HPP_

#include <unordered_map>

#include "MainMenu.hpp"
#include "PauseMenu.hpp"

namespace MyRpg {
    class MenuManager {
        public:
            MenuManager();
            ~MenuManager() = default;

            void update(const sf::Vector2f& mousePos, bool mousePressed, bool mouseReleased, const sf::Vector2f& position);
            void display(sf::RenderWindow& window);
            void handleEvent(const sf::Event& event);

            void setGameState(gameState state) { _currentState = state; }
            gameState getGameState() const { return _currentState; }

            Menu* getCurrentMenu() const;

            // Game state transitions
            void startGame();
            void pauseGame();
            void resumeGame();
            void openSettings();
            void openMainMenu();
            void quitGame();
            void saveGame();

        private:
            gameState _currentState;
            std::unordered_map<gameState, std::unique_ptr<Menu>> _menus;

            bool _quitRequested;

            void initializeMenus();
    };
}

#endif /* !MENUMANAGER_HPP_ */
