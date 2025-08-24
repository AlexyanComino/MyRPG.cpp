
#include "Potion.hpp"

namespace MyRpg {
    Potion::Potion(const std::string& name, const std::string& description,
                   const std::string& texturePath, int healAmount)
        : Item(name, description, POTION, texturePath), _healAmount(healAmount)
    {
    }

    void Potion::use()
    {
        std::cout << "Used " << _name << " - Healed " << _healAmount << " HP!" << std::endl; // To do
    }
}
