/*
** EPITECH PROJECT, 2025
** MyRPG.cpp
** File description:
** SfmlWindow
*/

#include "SfmlWindow.hpp"

namespace MyRpg {
    SfmlWindow::SfmlWindow() : AWindow(WIDTH, HEIGHT, 60, 1, 2),
        _videoMode(_width, _height, 32),
        _window(_videoMode, "The Blade of Eternity", sf::Style::Default),
        _mousePos(0, 0), _clock(), _view(sf::FloatRect(0, 0, static_cast<float>(_width), static_cast<float>(_height))),
        _viewPos(4850, 8400)
    {
        _window.setFramerateLimit(_framerate);
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
        // _window.setView(_view);
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