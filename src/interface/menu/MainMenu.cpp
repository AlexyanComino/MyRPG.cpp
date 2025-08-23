
#include "MainMenu.hpp"

namespace MyRpg {
    MainMenu::MainMenu() : Menu("assets/fonts/BreatheFireIii-PKLOB.ttf")
    {
        _title.setFont(_font);
        _title.setString("MyRPG.cpp");
        _title.setCharacterSize(150);
        _title.setFillColor(sf::Color::White);
        _title.setOrigin(_title.getGlobalBounds().width / 2, _title.getGlobalBounds().height / 2);

        initializeButtons();
    }

    void MainMenu::initializeButtons()
    {
        // Create buttons
        auto startButton = std::make_unique<Button>("Start Game", sf::Vector2f(0.0f, -100.0f), sf::Vector2f(400.0f, 100.0f), "assets/fonts/m6x11plus.ttf", 60);
        startButton->setCallback([this]() { if (_startGameCallback) _startGameCallback(); });

        auto settingsButton = std::make_unique<Button>("Settings", sf::Vector2f(0.0f, 150.0f), sf::Vector2f(400.0f, 100.0f), "assets/fonts/m6x11plus.ttf", 60);
        settingsButton->setCallback([this]() { if (_openSettingsCallback) _openSettingsCallback(); });

        auto quitButton = std::make_unique<Button>("Quit", sf::Vector2f(0.0f, 400.0f), sf::Vector2f(400.0f, 100.0f), "assets/fonts/m6x11plus.ttf", 60);
        quitButton->setCallback([this]() { if (_quitCallback) _quitCallback(); });

        addButton(std::move(startButton));
        addButton(std::move(settingsButton));
        addButton(std::move(quitButton));
    }

    void MainMenu::update(const sf::Vector2f& mousePos, bool mousePressed, bool mouseReleased, const sf::Vector2f& position)
    {
        for (auto& button : _buttons) {
            button->update(mousePos, mousePressed, mouseReleased, position);
        }

        _title.setPosition(sf::Vector2f(position.x, position.y - 500.0f));
    }

    void MainMenu::display(sf::RenderWindow& window)
    {
        window.draw(_title);
        for (auto& button : _buttons) {
            button->display(window);
        }
    }

    void MainMenu::setCallbacks(const std::vector<std::function<void()>> callbacks)
    {
        if (callbacks.size() != 3)
            throw std::invalid_argument("MainMenu::setCallbacks requires exactly 3 callbacks");
        _startGameCallback = callbacks[0];
        _openSettingsCallback = callbacks[1];
        _quitCallback = callbacks[2];
    }
}
