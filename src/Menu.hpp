#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <functional>
#include <memory>

namespace MyRpg {
    
    typedef enum buttonState {
        HOVERED,
        CLICKED,
        RELEASED,
        NOTHING
    } buttonState;

    typedef enum gameState {
        MAIN_MENU,
        GAME,
        PAUSE,
        SETTINGS,
        SAVE_MENU,
        SELECTOR,
        INVENTORY,
        MAP,
        SKILL_TREE,
        LOADING,
        END,
        CREDITS,
    } gameState;

    class Button {
    public:
        Button(const std::string& text, sf::Vector2f position, 
               std::function<void()> callback = nullptr);
        ~Button() = default;

        void update(sf::Vector2f mousePos, bool mousePressed, bool mouseReleased);
        void display(sf::RenderWindow& window);
        
        void setCallback(std::function<void()> callback) { _callback = callback; }
        buttonState getState() const { return _state; }
        bool isClicked() const { return _state == CLICKED; }
        bool isHovered() const { return _state == HOVERED; }
        
        void setPosition(sf::Vector2f position);
        void setSize(sf::Vector2f size);
        void setText(const std::string& text);
        
    private:
        sf::Text _text;
        sf::Font _font;
        sf::RectangleShape _background;
        sf::Vector2f _position;
        sf::Vector2f _size;
        buttonState _state;
        sf::Color _normalColor;
        sf::Color _hoverColor;
        sf::Color _clickColor;
        std::function<void()> _callback;
        
        void updateColors();
    };

    class Menu {
    public:
        Menu() = default;
        virtual ~Menu() = default;

        virtual void update(sf::Vector2f mousePos, bool mousePressed, bool mouseReleased) = 0;
        virtual void display(sf::RenderWindow& window) = 0;
        virtual void handleEvent(const sf::Event& event) {}
        
        void addButton(std::unique_ptr<Button> button);
        
    protected:
        std::vector<std::unique_ptr<Button>> _buttons;
        sf::Font _font;
    };

    class MainMenu : public Menu {
    public:
        MainMenu();
        ~MainMenu() = default;

        void update(sf::Vector2f mousePos, bool mousePressed, bool mouseReleased) override;
        void display(sf::RenderWindow& window) override;
        
        void setCallbacks(std::function<void()> startGame,
                         std::function<void()> openSettings,
                         std::function<void()> quit);

    private:
        sf::Text _title;
        std::function<void()> _startGameCallback;
        std::function<void()> _openSettingsCallback;
        std::function<void()> _quitCallback;
        
        void initializeButtons();
    };

    class PauseMenu : public Menu {
    public:
        PauseMenu();
        ~PauseMenu() = default;

        void update(sf::Vector2f mousePos, bool mousePressed, bool mouseReleased) override;
        void display(sf::RenderWindow& window) override;
        
        void setCallbacks(std::function<void()> resumeGame,
                         std::function<void()> saveGame,
                         std::function<void()> backToMenu);

    private:
        sf::Text _title;
        sf::RectangleShape _background;
        std::function<void()> _resumeGameCallback;
        std::function<void()> _saveGameCallback;
        std::function<void()> _backToMenuCallback;
        
        void initializeButtons();
    };

    class MenuManager {
    public:
        MenuManager();
        ~MenuManager() = default;

        void update(sf::Vector2f mousePos, bool mousePressed, bool mouseReleased);
        void display(sf::RenderWindow& window);
        void handleEvent(const sf::Event& event);
        
        void setGameState(gameState state) { _currentState = state; }
        gameState getGameState() const { return _currentState; }
        
        Menu* getCurrentMenu() const;
        
        // Game state transitions
        void startGame();
        void pauseGame();
        void resumeGame();
        void openSettings();
        void openMainMenu();
        void quitGame();
        void saveGame();
        
    private:
        gameState _currentState;
        std::unique_ptr<MainMenu> _mainMenu;
        std::unique_ptr<PauseMenu> _pauseMenu;
        
        bool _quitRequested;
        
        void initializeMenus();
    };
}

#endif /* !MENU_HPP_ */