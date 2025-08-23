
#include "Menu.hpp"

namespace MyRpg {
    Menu::Menu(const std::string& fontPath)
    {
        if (!_font.loadFromFile(fontPath)) {
            std::cerr << "Warning: Could not load title font" << std::endl;
        }
    }

    void Menu::addButton(std::unique_ptr<Button> button)
    {
        _buttons.push_back(std::move(button));
    }
}
