
#include "Core.hpp"

#include <iostream>

int main(void)
{
    try {
        MyRpg::Core core;

        while (core.windowIsOpen()) {
            core.handleEvents();
            core.update();
            core.display();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
