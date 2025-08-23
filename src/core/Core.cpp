
#include "Core.hpp"

namespace MyRpg {
    Core::Core()
    {
        _window = std::make_unique<SfmlWindow>();
        _map = std::make_unique<Map>("assets/map/ground/", "assets/map/foreground/", 7, "assets/map/collisions/res.coll");
        _menuManager = std::make_unique<MenuManager>();

        _entities.reserve(10);
        _entities.push_back(std::make_unique<Player<Torch>>("Player", BLUE, BLUE_TEAM,
            7763.0f, 5919.0f, 1.0f, 100, 100, 10, 5, 200.0f, 0, 1, 1.0f));
        _entities.push_back(std::make_unique<Warrior>("Warrior_RED", RED, RED_TEAM,
            8000.0f, 5919.0f, 1.0f, 100, 100, 10, 5, 200.0f, 0, 1, 1.0f));
        // _window->setViewCenter(_entities[0]->getX(), _entities[0]->getY());

        _playerIndex = 0;
    }

    void Core::handleEvents()
    {
        _window->setDt(_window->getClock().getElapsedTime().asSeconds());
        _window->getClock().restart();

        sf::Event event;
        bool mousePressed = false;
        bool mouseReleased = false;

        while (_window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window->close();
            if (event.type == sf::Event::MouseButtonPressed)
                mousePressed = true;
            if (event.type == sf::Event::MouseButtonReleased)
                mouseReleased = true;

            _menuManager->handleEvent(event);
        }

        sf::Vector2f mouseWorldPos = _window->getWindow().mapPixelToCoords(sf::Mouse::getPosition(_window->getWindow()));

        _menuManager->update(mouseWorldPos, mousePressed, mouseReleased, _window->getView().getCenter());

        if (_menuManager->getGameState() == GAME) {
            _entities[_playerIndex]->handleEvents(_window->getDt(), _map->getCollisions(), _entities);
            _window->setViewCenter(_entities[_playerIndex]->getX(), _entities[_playerIndex]->getY());
        }
    }

    void Core::update()
    {
        if (_menuManager->getGameState() == MAIN_MENU) {
            _window->setZoom(2.0f);
            _window->setViewCenter(4850.0f, 8400.0f);
        }
        if (_menuManager->getGameState() != GAME)
            return;

        _window->setZoom(0.5f);
        for (auto& entity : _entities) {
            if (intRectIsInView(entity->getHitbox()))
                entity->setInView(true);
            else
                entity->setInView(false);
        }

        for (std::size_t i = 0; i < _entities.size(); i++) {
            for (std::size_t j = i + 1; j < _entities.size(); j++) {
                if (i == j)
                    continue;
                if (_entities[i]->getY() > _entities[j]->getY()) {
                    _playerIndex = (_playerIndex == i) ? j : (_playerIndex == j) ? i : _playerIndex;
                    auto tmp = std::move(_entities[i]);
                    _entities[i] = std::move(_entities[j]);
                    _entities[j] = std::move(tmp);
                }
            }
        }

        for (auto& entity : _entities)
            entity->update();
    }

    void Core::displayCollisions()
    {
        Collisions collisionsMap = _map->getCollisions();
        std::size_t col = static_cast<std::size_t>(_entities[_playerIndex]->getX() / WIDTH);
        std::size_t row = static_cast<std::size_t>(_entities[_playerIndex]->getY() / HEIGHT);

        if (col >= collisionsMap.getNbColumns() || row >= collisionsMap.getNbRows())
            return;

        for (std::size_t i = 0; i < collisionsMap.regions[col][row].size; i++) {
            collisionsMap.rect.left = static_cast<int>(collisionsMap.regions[col][row].positions[i].x);
            collisionsMap.rect.top = static_cast<int>(collisionsMap.regions[col][row].positions[i].y);
            if (!intRectIsInView(collisionsMap.rect))
                continue;
            collisionsMap.shape.setPosition(sf::Vector2f(static_cast<float>(collisionsMap.rect.left), static_cast<float>(collisionsMap.rect.top)));
            _window->draw(collisionsMap.shape);
        }
        collisionsMap.regionShape.setPosition(sf::Vector2f(static_cast<float>(col) * WIDTH, static_cast<float>(row) * HEIGHT));
       _window->draw(collisionsMap.regionShape);
    }

    void Core::display()
    {
        _window->clear();

        gameState state = _menuManager->getGameState();
        if (state == GAME || state == PAUSE || state == MAIN_MENU) {
            _window->resetView();
            for (int i = 0; i < _map->getSize(); i++)
                _window->draw(_map->getGroundSpriteAt(i));

            for (auto& entity : _entities) {
                entity->display(_window->getWindow());
            }

            for (int i = 0; i < _map->getSize(); i++) {
                _window->draw(_map->getForegroundSprites()[i]);
            }

            displayCollisions();
        }
        _menuManager->display(_window->getWindow());

        _window->display();
    }

    bool Core::intRectIsInView(const sf::IntRect& rect)
    {
        sf::Vector2f viewPos = _window->getWindow().getView().getCenter();
        sf::Vector2f viewSize = _window->getWindow().getView().getSize();

        if (rect.left + rect.width < viewPos.x - viewSize.x ||
            rect.left > viewPos.x + viewSize.x ||
            rect.top + rect.height < viewPos.y - viewSize.y ||
            rect.top > viewPos.y + viewSize.y)
            return false;
        return true;
    }
}
