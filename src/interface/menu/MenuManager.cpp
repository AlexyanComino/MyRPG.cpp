
#include "MenuManager.hpp"

namespace MyRpg {
    MenuManager::MenuManager() : _currentState(MAIN_MENU), _quitRequested(false)
    {
        initializeMenus();
    }

    void MenuManager::initializeMenus()
    {
        _menus[MAIN_MENU] = std::make_unique<MainMenu>();
        _menus[MAIN_MENU]->setCallbacks(std::vector<std::function<void()>>{
            [this]() { startGame(); },
            [this]() { openSettings(); },
            [this]() { quitGame(); }
        });

        _menus[PAUSE] = std::make_unique<PauseMenu>();
        _menus[PAUSE]->setCallbacks(std::vector<std::function<void()>>{
            [this]() { resumeGame(); },
            [this]() { saveGame(); },
            [this]() { openMainMenu(); }
        });
    }

    void MenuManager::update(const sf::Vector2f& mousePos, bool mousePressed, bool mouseReleased, const sf::Vector2f& position)
    {
        Menu* currentMenu = getCurrentMenu();
        if (currentMenu) {
            currentMenu->update(mousePos, mousePressed, mouseReleased, position);
        }
    }

    void MenuManager::display(sf::RenderWindow& window)
    {
        Menu* currentMenu = getCurrentMenu();
        if (currentMenu) {
            currentMenu->display(window);
        }
    }

    void MenuManager::handleEvent(const sf::Event& event)
    {
        Menu* currentMenu = getCurrentMenu();
        if (currentMenu) {
            currentMenu->handleEvent(event);
        }

        // Handle escape key to pause/unpause
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (_currentState == GAME) {
                    pauseGame();
                } else if (_currentState == PAUSE) {
                    resumeGame();
                }
            }
        }
    }

    Menu* MenuManager::getCurrentMenu() const
    {
        switch (_currentState) {
            case MAIN_MENU:
                return _menus.at(MAIN_MENU).get();
            case PAUSE:
                return _menus.at(PAUSE).get();
            default:
                return nullptr;
        }
    }

    void MenuManager::startGame()
    {
        _currentState = GAME;
    }

    void MenuManager::pauseGame()
    {
        if (_currentState == GAME) {
            _currentState = PAUSE;
        }
    }

    void MenuManager::resumeGame()
    {
        if (_currentState == PAUSE) {
            _currentState = GAME;
        }
    }

    void MenuManager::openSettings()
    {
        _currentState = SETTINGS;
    }

    void MenuManager::openMainMenu()
    {
        _currentState = MAIN_MENU;
    }

    void MenuManager::quitGame()
    {
        _quitRequested = true;
        throw std::runtime_error("Quit requested");
        // Temporary
    }

    void MenuManager::saveGame()
    {
        std::cout << "Game saved!" << std::endl;
        // Temporary
    }
}
