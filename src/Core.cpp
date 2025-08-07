
#include "Core.hpp"

namespace MyRpg {
    Core::Core()
    {
        _window = std::make_unique<SfmlWindow>();
        _map = std::make_unique<Map>("assets/map/ground_1024/", "assets/map/foreground_1024/", 14);
    }

    Core::~Core()
    {
    }

    void Core::handleEvents()
    {
        sf::Event event;
        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->close();
        }
    }

    void Core::update()
    {

    }

    void Core::display()
    {
        _window->clear();

        _window->resetView();
        for (int i = 0; i < _map->getSize(); i++) {
            _window->draw(_map->getGroundSprites()[i]);
            // _window->draw(_map->getForegroundSprites()[i]);
        }

        _window->display();
    }

    void Core::destroy()
    {

    }
}