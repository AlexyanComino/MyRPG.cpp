
#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <SFML/Graphics.hpp>

namespace MyRpg {
    class Clock {
        public:
            Clock() = default;
            ~Clock() = default;

            const float getSeconds() const { return _seconds; };

            void update();
            void restart() { _clock.restart(); };

        private:
            sf::Clock _clock;
            sf::Time _time;
            float _seconds;
    };
}

#endif /* !CLOCK_HPP_ */
