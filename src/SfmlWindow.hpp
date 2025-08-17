
#ifndef SFMLWINDOW_HPP_
#define SFMLWINDOW_HPP_

#include "AWindow.hpp"
#include "constants.hpp"

#include <SFML/Graphics.hpp>

namespace MyRpg {
    class SfmlWindow : public AWindow {
        public:
            SfmlWindow();
            ~SfmlWindow();

            sf::RenderWindow& getWindow() override { return _window; };

            bool isOpen() override { return _window.isOpen(); };
            void resetView() override;
            void setViewCenter(float x, float y) override;

            void clear() override { _window.clear(); };
            void display() override { _window.display(); };
            void close() override { _window.close(); };

            void draw(const sf::Drawable& sprite) override;
            bool pollEvent(sf::Event& event) override;

            sf::Clock& getClock() { return _clock; };

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
