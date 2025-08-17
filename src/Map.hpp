
#ifndef MAP_HPP_
#define MAP_HPP_

#include <vector>
#include <filesystem>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Collisions.hpp"

namespace MyRpg {
    class Map {
        public:
            Map(const std::string& groundPath, const std::string& foregroundPath,
                const int& mapWidth, const std::string& collisionsFilePath);
            ~Map();


            const std::vector<sf::Sprite>& getGroundSprites() const { return _groundSprites; }
            const sf::Sprite& getGroundSpriteAt(const int& index) const;
            const sf::Sprite& getForegroundSpriteAt(const int& index) const;
            const std::vector<sf::Sprite>& getForegroundSprites() const { return _foregroundSprites; }

            const int getSize() const { return _size; };
            Collisions getCollisions() const { return _collisions; };

        protected:
        private:
            Collisions _collisions;

            std::vector<sf::Texture> _groundTextures;
            std::vector<sf::Texture> _foregroundTextures;
            std::vector<sf::Sprite> _groundSprites;
            std::vector<sf::Sprite> _foregroundSprites;

            const int _mapWidth;
            int _size;
    };
}

#endif /* !MAP_HPP_ */
