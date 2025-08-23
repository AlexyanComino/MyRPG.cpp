
#include "Clock.hpp"

namespace MyRpg {

    void Clock::update()
    {
        _time = _clock.getElapsedTime();
        _seconds = static_cast<float>(_time.asMicroseconds() / 1000000.0);
    }
}
