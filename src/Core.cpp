
#include "Core.hpp"

namespace MyRpg {
    Core::Core()
    {
        _window = std::make_unique<SfmlWindow>();
        _map = std::make_unique<Map>("assets/map/ground/", "assets/map/foreground/", 7, "assets/map/collisions/res.coll");
        _menuManager = std::make_unique<MenuManager>();
        _inventory = std::make_unique<Inventory>();
        _playerStatus = std::make_unique<PlayerStatus>();

        _entities.reserve(10);
        _entities.push_back(std::make_unique<Player<Warrior>>("Warrior1", BLUE, BLUE_TEAM, 
            7763.0f, 5919.0f, 1.0f, 100, 100, 10, 5, 200.0f, 0, 1, 1.0f));
        _window->setViewCenter(_entities[0]->getX(), _entities[0]->getY());

        _playerIndex = 0;
        
        // Add some test items to inventory
        _inventory->addGold(100);
        auto testSword = std::make_unique<Weapon>("Iron Sword", "A basic iron sword", 15, 1.2f);
        testSword->setTexture("assets/items/weapons/iron_sword.png");
        _inventory->addItem(std::move(testSword));
        
        auto testPotion = std::make_unique<Potion>("Health Potion", "Restores 50 HP", 50);
        testPotion->setTexture("assets/items/potions/health_potion.png");
        _inventory->addItem(std::move(testPotion));
    }

    Core::~Core()
    {
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
                
            // Handle inventory toggle
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::I) {
                    if (_menuManager->getGameState() == GAME) {
                        _inventory->toggle();
                        if (_inventory->isOpen()) {
                            _menuManager->setGameState(INVENTORY);
                        }
                    } else if (_menuManager->getGameState() == INVENTORY) {
                        _inventory->close();
                        _menuManager->setGameState(GAME);
                    }
                }
            }
                
            _menuManager->handleEvent(event);
        }
        
        // Get mouse position
        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(_window->getWindow());
        sf::Vector2f mouseWorldPos = _window->getWindow().mapPixelToCoords(mousePixelPos);
        
        // Update menu system
        _menuManager->update(mouseWorldPos, mousePressed, mouseReleased);
        
        // Update inventory if open
        if (_menuManager->getGameState() == INVENTORY) {
            _inventory->update(mouseWorldPos, mousePressed);
        }
        
        // Only handle game events when in game state
        if (_menuManager->getGameState() == GAME) {
            _entities[_playerIndex]->handleEvents(_window->getDt(), _map->getCollisions());
            _window->setViewCenter(_entities[_playerIndex]->getX(), _entities[_playerIndex]->getY());
        }
    }

    void Core::update()
    {
        // Only update entities when in game state
        if (_menuManager->getGameState() == GAME) {
            for (auto& entity : _entities)
                entity->update();
        }
    }

    void Core::displayCollisions()
    {
        Collisions collisionsMap = _map->getCollisions();
        std::size_t col = _entities[_playerIndex]->getX() / WIDTH;
        std::size_t row = _entities[_playerIndex]->getY() / HEIGHT;

        if (col >= collisionsMap.getNbColumns() || row >= collisionsMap.getNbRows())
            return;
        
        for (std::size_t i = 0;i < collisionsMap.regions[col][row].size; i++) {
            collisionsMap.rect.left = collisionsMap.regions[col][row].positions[i].x;
            collisionsMap.rect.top = collisionsMap.regions[col][row].positions[i].y;
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

        // Render game world when in game, pause, or inventory state
        if (_menuManager->getGameState() == GAME || _menuManager->getGameState() == PAUSE || _menuManager->getGameState() == INVENTORY) {
            _window->resetView();
            for (int i = 0; i < _map->getSize(); i++)
                _window->draw(_map->getGroundSpriteAt(i));

            for (auto& entity : _entities) {
                entity->display(_window->getWindow());
            }

            for (int i = 0; i < _map->getSize(); i++)
                _window->draw(_map->getForegroundSprites()[i]);

            displayCollisions();
        }
        
        // Always render menu system on top
        _menuManager->display(_window->getWindow());
        
        // Render inventory if open
        if (_menuManager->getGameState() == INVENTORY) {
            _inventory->display(_window->getWindow());
            _playerStatus->display(_window->getWindow());
        }

        _window->display();
    }

    void Core::destroy()
    {

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