
#ifndef AWINDOW_HPP_
#define AWINDOW_HPP_

#include "IWindow.hpp"

namespace MyRpg {
    class AWindow : public IWindow {
        public:
            AWindow(const unsigned int width, const unsigned int height,
                    const unsigned int framerate, float dt, float zoom) :
                    _width(width), _height(height), _framerate(framerate),
                    _dt(dt), _zoom(zoom) {};
            ~AWindow() = default;

            virtual sf::RenderWindow& getWindow() = 0;

            virtual bool isOpen() = 0;

            virtual void clear() = 0;
            virtual void draw(const sf::Drawable& sprite) = 0;
            virtual bool pollEvent(sf::Event& event) = 0;
            virtual void display() = 0;
            virtual void close() = 0;
            virtual void resetView() = 0;
            virtual void setViewCenter(float x, float y) = 0;

            // Getters
            const unsigned int getWidth() const { return _width; };
            const unsigned int getHeight() const { return _height; };
            const unsigned int getFramerate() const { return _framerate; };
            const float getDt() const { return _dt; };
            const float getZoom() const { return _zoom; };

            virtual sf::Clock& getClock() = 0;

            // Setters
            void setDt(float dt) { _dt = dt; };
            void setZoom(float zoom) { _zoom = zoom; };

        protected:
                const unsigned int _width;
                const unsigned int _height;
                const unsigned int _framerate;
                
                float _dt;
                float _zoom;
        private:
    };
}

#endif /* !AWINDOW_HPP_ */
