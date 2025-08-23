#include "Menu.hpp"
#include <iostream>

namespace MyRpg {

    // Button Implementation
    Button::Button(const std::string& text, sf::Vector2f position, 
                   std::function<void()> callback)
        : _position(position), _size(200.0f, 50.0f), _state(NOTHING), 
          _normalColor(sf::Color::Blue), _hoverColor(sf::Color::Cyan), 
          _clickColor(sf::Color::Green), _callback(callback)
    {
        // Load default font (in a real implementation, you'd load from file)
        if (!_font.loadFromFile("assets/fonts/default.ttf")) {
            // Use system font as fallback
            std::cerr << "Warning: Could not load font, using system default" << std::endl;
        }
        
        _text.setFont(_font);
        _text.setString(text);
        _text.setCharacterSize(24);
        _text.setFillColor(sf::Color::White);
        
        _background.setSize(_size);
        _background.setFillColor(_normalColor);
        _background.setOutlineColor(sf::Color::White);
        _background.setOutlineThickness(2.0f);
        
        setPosition(position);
    }

    void Button::update(sf::Vector2f mousePos, bool mousePressed, bool mouseReleased)
    {
        sf::FloatRect bounds = _background.getGlobalBounds();
        bool mouseInBounds = bounds.contains(mousePos);
        
        if (mousePressed && mouseInBounds) {
            _state = CLICKED;
            if (_callback) {
                _callback();
            }
        } else if (mouseReleased && _state == CLICKED && mouseInBounds) {
            _state = RELEASED;
        } else if (mouseInBounds) {
            _state = HOVERED;
        } else {
            _state = NOTHING;
        }
        
        updateColors();
    }

    void Button::display(sf::RenderWindow& window)
    {
        window.draw(_background);
        window.draw(_text);
    }

    void Button::setPosition(sf::Vector2f position)
    {
        _position = position;
        _background.setPosition(_position);
        
        // Center text in button
        sf::FloatRect textBounds = _text.getLocalBounds();
        sf::Vector2f textPos(
            _position.x + (_size.x - textBounds.width) / 2.0f - textBounds.left,
            _position.y + (_size.y - textBounds.height) / 2.0f - textBounds.top
        );
        _text.setPosition(textPos);
    }

    void Button::setSize(sf::Vector2f size)
    {
        _size = size;
        _background.setSize(_size);
        setPosition(_position); // Recenter text
    }

    void Button::setText(const std::string& text)
    {
        _text.setString(text);
        setPosition(_position); // Recenter text
    }

    void Button::updateColors()
    {
        switch (_state) {
            case CLICKED:
                _background.setFillColor(_clickColor);
                break;
            case HOVERED:
                _background.setFillColor(_hoverColor);
                break;
            default:
                _background.setFillColor(_normalColor);
                break;
        }
    }

    // Menu Implementation
    void Menu::addButton(std::unique_ptr<Button> button)
    {
        _buttons.push_back(std::move(button));
    }

    // MainMenu Implementation
    MainMenu::MainMenu()
    {
        // Load font
        if (!_font.loadFromFile("assets/fonts/title.ttf")) {
            std::cerr << "Warning: Could not load title font" << std::endl;
        }
        
        _title.setFont(_font);
        _title.setString("MyRPG.cpp");
        _title.setCharacterSize(72);
        _title.setFillColor(sf::Color::White);
        _title.setPosition(400.0f, 100.0f);
        
        initializeButtons();
    }

    void MainMenu::initializeButtons()
    {
        // Create buttons
        auto startButton = std::make_unique<Button>("Start Game", sf::Vector2f(500.0f, 300.0f));
        startButton->setCallback([this]() { if (_startGameCallback) _startGameCallback(); });
        
        auto settingsButton = std::make_unique<Button>("Settings", sf::Vector2f(500.0f, 380.0f));
        settingsButton->setCallback([this]() { if (_openSettingsCallback) _openSettingsCallback(); });
        
        auto quitButton = std::make_unique<Button>("Quit", sf::Vector2f(500.0f, 460.0f));
        quitButton->setCallback([this]() { if (_quitCallback) _quitCallback(); });
        
        addButton(std::move(startButton));
        addButton(std::move(settingsButton));
        addButton(std::move(quitButton));
    }

    void MainMenu::update(sf::Vector2f mousePos, bool mousePressed, bool mouseReleased)
    {
        for (auto& button : _buttons) {
            button->update(mousePos, mousePressed, mouseReleased);
        }
    }

    void MainMenu::display(sf::RenderWindow& window)
    {
        window.draw(_title);
        for (auto& button : _buttons) {
            button->display(window);
        }
    }

    void MainMenu::setCallbacks(std::function<void()> startGame,
                               std::function<void()> openSettings,
                               std::function<void()> quit)
    {
        _startGameCallback = startGame;
        _openSettingsCallback = openSettings;
        _quitCallback = quit;
    }

    // PauseMenu Implementation
    PauseMenu::PauseMenu()
    {
        // Load font
        if (!_font.loadFromFile("assets/fonts/title.ttf")) {
            std::cerr << "Warning: Could not load title font" << std::endl;
        }
        
        _title.setFont(_font);
        _title.setString("Game Paused");
        _title.setCharacterSize(48);
        _title.setFillColor(sf::Color::White);
        _title.setPosition(450.0f, 200.0f);
        
        // Semi-transparent background
        _background.setSize(sf::Vector2f(1280.0f, 720.0f));
        _background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black
        _background.setPosition(0.0f, 0.0f);
        
        initializeButtons();
    }

    void PauseMenu::initializeButtons()
    {
        auto resumeButton = std::make_unique<Button>("Resume", sf::Vector2f(500.0f, 300.0f));
        resumeButton->setCallback([this]() { if (_resumeGameCallback) _resumeGameCallback(); });
        
        auto saveButton = std::make_unique<Button>("Save Game", sf::Vector2f(500.0f, 380.0f));
        saveButton->setCallback([this]() { if (_saveGameCallback) _saveGameCallback(); });
        
        auto menuButton = std::make_unique<Button>("Main Menu", sf::Vector2f(500.0f, 460.0f));
        menuButton->setCallback([this]() { if (_backToMenuCallback) _backToMenuCallback(); });
        
        addButton(std::move(resumeButton));
        addButton(std::move(saveButton));
        addButton(std::move(menuButton));
    }

    void PauseMenu::update(sf::Vector2f mousePos, bool mousePressed, bool mouseReleased)
    {
        for (auto& button : _buttons) {
            button->update(mousePos, mousePressed, mouseReleased);
        }
    }

    void PauseMenu::display(sf::RenderWindow& window)
    {
        window.draw(_background);
        window.draw(_title);
        for (auto& button : _buttons) {
            button->display(window);
        }
    }

    void PauseMenu::setCallbacks(std::function<void()> resumeGame,
                                std::function<void()> saveGame,
                                std::function<void()> backToMenu)
    {
        _resumeGameCallback = resumeGame;
        _saveGameCallback = saveGame;
        _backToMenuCallback = backToMenu;
    }

    // MenuManager Implementation
    MenuManager::MenuManager() : _currentState(MAIN_MENU), _quitRequested(false)
    {
        initializeMenus();
    }

    void MenuManager::initializeMenus()
    {
        _mainMenu = std::make_unique<MainMenu>();
        _mainMenu->setCallbacks(
            [this]() { startGame(); },
            [this]() { openSettings(); },
            [this]() { quitGame(); }
        );
        
        _pauseMenu = std::make_unique<PauseMenu>();
        _pauseMenu->setCallbacks(
            [this]() { resumeGame(); },
            [this]() { saveGame(); },
            [this]() { openMainMenu(); }
        );
    }

    void MenuManager::update(sf::Vector2f mousePos, bool mousePressed, bool mouseReleased)
    {
        Menu* currentMenu = getCurrentMenu();
        if (currentMenu) {
            currentMenu->update(mousePos, mousePressed, mouseReleased);
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
                return _mainMenu.get();
            case PAUSE:
                return _pauseMenu.get();
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
        // In a real implementation, you'd handle this in the main game loop
    }

    void MenuManager::saveGame()
    {
        std::cout << "Game saved!" << std::endl;
        // Implement save functionality
    }
}