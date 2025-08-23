
#ifndef CORE_HPP_
#define CORE_HPP_

#include <memory>
#include <vector>

#include "Map.hpp"
#include "window/SfmlWindow.hpp"
#include "Torch.hpp"
#include "Warrior.hpp"
#include "Player.hpp"
#include "MenuManager.hpp"

namespace MyRpg {
    class Core {
        public:
            Core();
            ~Core() = default;

            bool windowIsOpen() const { return _window->isOpen(); };

            void handleEvents();
            void update();
            void display();

            void destroy() {};

            void displayCollisions();

            bool intRectIsInView(const sf::IntRect& rect);
        protected:
        private:
            std::unique_ptr<IWindow> _window;
            std::unique_ptr<Map> _map;
            std::unique_ptr<MenuManager> _menuManager;
            std::vector<std::unique_ptr<IEntity>> _entities;

            std::size_t _playerIndex;
    };
}

#endif /* !CORE_HPP_ */
