
#ifndef COLLISIONS_HPP_
#define COLLISIONS_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

#include "constants.hpp"
#include "IEntity.hpp"

namespace MyRpg {

    typedef struct region_s {
        std::size_t size = 0;
        std::vector<sf::Vector2f> positions;
        sf::IntRect rect;
    } region_t;

    class Collisions {
        public:
            Collisions(const std::string& collisionsFilePath);
            ~Collisions() = default;

            const std::size_t getNbColumns() const { return _columns; };
            const std::size_t getNbRows() const { return _rows; };

            bool isIntRectCollidingWithEntities(const sf::IntRect hitbox, const IEntity* caller, const std::vector<std::unique_ptr<IEntity>>& entities);
            bool isIntRectCollidingWithMap(const sf::IntRect hitbox);
            bool isIntRectColliding(const sf::IntRect hitbox, const IEntity* caller, const std::vector<std::unique_ptr<IEntity>>& entities);

            sf::IntRect rect;
            sf::RectangleShape shape;
            sf::RectangleShape regionShape;

            std::vector<std::vector<region_t>> regions;

        protected:
        private:
            std::vector<std::vector<region_t>> createRegions(const std::string& collisionsFilePath);
            bool checkRegion(const sf::IntRect hitbox, std::size_t col, std::size_t row);

            std::size_t _rows;
            std::size_t _columns;
            std::size_t _size;
    };
}

#endif /* !COLLISIONS_HPP_ */
