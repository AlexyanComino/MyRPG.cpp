
#ifndef POTION_HPP_
#define POTION_HPP_

#include "Item.hpp"

namespace MyRpg {
    class Potion : public Item {
        public:
            Potion(const std::string& name, const std::string& description,
                const std::string& texturePath, int healAmount);
            ~Potion() = default;

            const int getHealAmount() const { return _healAmount; }
            void use();

        private:
            int _healAmount;
    };
}

#endif /* !POTION_HPP_ */
