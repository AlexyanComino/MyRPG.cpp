
#include "Core.hpp"

#include <iostream>

int main(void)
{
    MyRpg::Core core;

    while (core.windowIsOpen()) {
        core.handleEvents();
        core.update();
        core.display();
    }
    core.destroy();
    return 0;
}
