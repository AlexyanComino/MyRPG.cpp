
#include "PauseMenu.hpp"

namespace MyRpg {
    PauseMenu::PauseMenu() : Menu("assets/fonts/Burbank-Big-Condensed-Black.ttf")
    {
        _title.setFont(_font);
        _title.setString("Game Paused");
        _title.setCharacterSize(48);
        _title.setFillColor(sf::Color::White);
        _title.setOrigin(_title.getGlobalBounds().width / 2, _title.getGlobalBounds().height / 2);

        // Semi-transparent background
        _background.setSize(sf::Vector2f(1280.0f, 720.0f));
        _background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black
        _background.setOrigin(_background.getGlobalBounds().width / 2, _background.getGlobalBounds().height / 2);

        initializeButtons();
    }

    void PauseMenu::initializeButtons()
    {
        auto resumeButton = std::make_unique<Button>("Resume", sf::Vector2f(0.0f, 100.0f), sf::Vector2f(200.0f, 50.0f));
        resumeButton->setCallback([this]() { if (_resumeGameCallback) _resumeGameCallback(); });

        auto saveButton = std::make_unique<Button>("Save Game", sf::Vector2f(0.0f, 180.0f), sf::Vector2f(200.0f, 50.0f));
        saveButton->setCallback([this]() { if (_saveGameCallback) _saveGameCallback(); });

        auto menuButton = std::make_unique<Button>("Main Menu", sf::Vector2f(0.0f, 260.0f), sf::Vector2f(200.0f, 50.0f));
        menuButton->setCallback([this]() { if (_backToMenuCallback) _backToMenuCallback(); });

        addButton(std::move(resumeButton));
        addButton(std::move(saveButton));
        addButton(std::move(menuButton));
    }

    void PauseMenu::update(const sf::Vector2f& mousePos, bool mousePressed, bool mouseReleased, const sf::Vector2f& position)
    {
        for (auto& button : _buttons) {
            button->update(mousePos, mousePressed, mouseReleased, position);
        }

        _background.setPosition(position.x, position.y);
        _title.setPosition(sf::Vector2f(position.x, position.y - 100.0f));
    }

    void PauseMenu::display(sf::RenderWindow& window)
    {
        window.draw(_background);
        window.draw(_title);
        for (auto& button : _buttons) {
            button->display(window);
        }
    }

    void PauseMenu::setCallbacks(const std::vector<std::function<void()>> callbacks)
    {
        if (callbacks.size() != 3)
            throw std::invalid_argument("PauseMenu::setCallbacks requires exactly 3 callbacks");
        _resumeGameCallback = callbacks[0];
        _saveGameCallback = callbacks[1];
        _backToMenuCallback = callbacks[2];
    }
}
