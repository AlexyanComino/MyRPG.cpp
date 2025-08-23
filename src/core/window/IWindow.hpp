
#ifndef IWINDOW_HPP_
#define IWINDOW_HPP_

#include <SFML/Graphics.hpp>

namespace MyRpg {
    class IWindow {
        public:
            virtual ~IWindow() = default;

            virtual bool isOpen() = 0;

            virtual sf::RenderWindow& getWindow() = 0;

            virtual void clear() = 0;
            virtual void draw(const sf::Drawable& sprite) = 0;
            virtual bool pollEvent(sf::Event& event) = 0;
            virtual void display() = 0;
            virtual void close() = 0;
            virtual void resetView() = 0;
            virtual void setViewCenter(float x, float y) = 0;

            // Getters
            virtual const unsigned int getWidth() const = 0;
            virtual const unsigned int getHeight() const = 0;
            virtual const unsigned int getFramerate() const = 0;
            virtual const float getDt() const = 0;
            virtual const float getZoom() const = 0;

            virtual sf::Clock& getClock() = 0;

            // Setters
            virtual void setDt(float dt) = 0;
            virtual void setZoom(float zoom) = 0;

        protected:
        private:
    };
}

#endif /* !IWINDOW_HPP_ */
