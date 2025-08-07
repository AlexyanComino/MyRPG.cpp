
#ifndef SFMLWINDOW_HPP_
#define SFMLWINDOW_HPP_

#include "AWindow.hpp"

#include <SFML/Graphics.hpp>

namespace MyRpg {
    class SfmlWindow : public AWindow {
        public:
            SfmlWindow();
            ~SfmlWindow();

            bool isOpen() override { return _window.isOpen(); };
            void resetView() override;

            void clear() override { _window.clear(); };
            void display() override { _window.display(); };
            void close() override { _window.close(); };

            void draw() override { _window.draw(sf::Sprite()); }; // Default draw method, can be overridden
            void draw(const sf::Sprite& sprite) override;
            bool pollEvent(sf::Event& event) override;

        protected:
        private:
            sf::VideoMode _videoMode;
            sf::RenderWindow _window;
            sf::Vector2f _mousePos;
            sf::Clock _clock;
            sf::View _view;
            sf::Vector2f _viewPos;   
    };
}

#endif /* !SFMLWINDOW_HPP_ */
