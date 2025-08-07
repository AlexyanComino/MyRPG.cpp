
#ifndef CORE_HPP_
#define CORE_HPP_

#include "Map.hpp"

#include "SfmlWindow.hpp"

#include <memory>

namespace MyRpg {
    class Core {
        public:
            Core();
            ~Core();

            bool windowIsOpen() const { return _window->isOpen(); };

            void handleEvents();
            void update();
            void display();

            void destroy();

        protected:
        private:
            std::unique_ptr<IWindow> _window;
            std::unique_ptr<Map> _map;
    };
}

#endif /* !CORE_HPP_ */
