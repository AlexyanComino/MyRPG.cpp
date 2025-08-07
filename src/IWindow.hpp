
#ifndef IWINDOW_HPP_
#define IWINDOW_HPP_

#include <SFML/Graphics.hpp>

namespace MyRpg {
    class IWindow {
        public:
            virtual ~IWindow() = default;

            virtual bool isOpen() = 0;

            virtual void clear() = 0;
            virtual void draw() = 0;
            virtual void draw(const sf::Sprite& sprite) = 0;
            virtual bool pollEvent(sf::Event& event) = 0;
            virtual void display() = 0;
            virtual void close() = 0;
            virtual void resetView() = 0;

        protected:
        private:
    };
}

#endif /* !IWINDOW_HPP_ */
