/*
** EPITECH PROJECT, 2025
** MyRPG.cpp
** File description:
** SfmlWindow
*/

#include "SfmlWindow.hpp"
#include <iostream>

namespace MyRpg {
    SfmlWindow::SfmlWindow() : AWindow(WIDTH, HEIGHT, 60, 1.0f, 2.0f),
        _videoMode(_width, _height, 32U),
        _window(_videoMode, "The Blade of Eternity", sf::Style::Default),
        _mousePos(0.0f, 0.0f), _clock(), _view(sf::FloatRect(0.0f, 0.0f, static_cast<float>(_width), static_cast<float>(_height))),
        _viewPos(4850.0f, 8400.0f)
    {
        _window.setFramerateLimit(_framerate);

        _view.setCenter(_viewPos);
        _view.zoom(_zoom);
        _window.setView(_view);
    }

    SfmlWindow::~SfmlWindow()
    {
    }

    void SfmlWindow::resetView()
    {
        const sf::View& currentView = this->_window.getView();

        if (currentView.getCenter() != _view.getCenter() ||
            currentView.getSize() != _view.getSize() ||
            currentView.getViewport() != _view.getViewport())
        {
            _window.setView(_view);
        }
    }

    void SfmlWindow::setViewCenter(float x, float y)
    {
        _view.setCenter(x, y);
        _viewPos = sf::Vector2f(x, y);
        // _window.setView(_view);
    }

    void SfmlWindow::setZoom(float zoom)
    {
        if (_zoom == zoom)
            return;

        _zoom = zoom;
        _view.zoom(zoom);
    }

    void SfmlWindow::draw(const sf::Drawable& object)
    {
        _window.draw(object);
    }

    bool SfmlWindow::pollEvent(sf::Event& event)
    {
        return _window.pollEvent(event);
    }
}
