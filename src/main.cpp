#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::RectangleShape rectangle;
    rectangle.setSize({100.f, 100.f});
    rectangle.setFillColor(sf::Color::Red);
    rectangle.setPosition({960.f, 540.f});

    while (window.isOpen()) {
        window.clear();
        window.draw(rectangle);
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.display();
    }
}
