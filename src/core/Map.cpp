
#include "Map.hpp"

namespace MyRpg {
    Map::Map(const std::string& groundFolder, const std::string& foregroundFolder,
            const int& mapWidth, const std::string& collisionsFilePath) :
            _mapWidth(mapWidth), _size(0), _collisions(collisionsFilePath)
    {
        _groundTextures.reserve(50);
        _foregroundTextures.reserve(50);
        _groundSprites.reserve(50);
        _foregroundSprites.reserve(50);

        int rowCount = 0;
        int columnCount = 0;
        
        if (!std::filesystem::exists(groundFolder) || !std::filesystem::is_directory(groundFolder)) {
            std::cerr << "Ground folder does not exist or is not a directory: " << groundFolder << std::endl;
            return;
        }
        int tileCount = 0;
        std::string groundPath = groundFolder + "tile_" + std::to_string(tileCount) + ".png";
        
        while (std::filesystem::exists(groundPath)) {
            std::cout << "Loading ground texture: " << groundPath << std::endl;
            _groundTextures.emplace_back();
            _groundTextures.back().loadFromFile(groundPath);
            _groundSprites.emplace_back(sf::Sprite(_groundTextures.back()));
            _groundSprites.back().setScale(sf::Vector2f(2.1f, 2.1f));
            _groundSprites.back().setPosition(static_cast<float>(columnCount * 2048 * 2.1f), static_cast<float>(rowCount * 2048 * 2.1f));
            _size++;
            columnCount++;
            if (columnCount >= _mapWidth) {
                columnCount = 0;
                rowCount++;
            }
            tileCount++;
            groundPath = groundFolder + "tile_" + std::to_string(tileCount) + ".png";
        }
        rowCount = 0;
        columnCount = 0;

        if (!std::filesystem::exists(foregroundFolder) || !std::filesystem::is_directory(foregroundFolder)) {
            std::cerr << "Foreground folder does not exist or is not a directory: " << foregroundFolder << std::endl;
            return;
        }
        tileCount = 0;
        std::string foregroundPath = foregroundFolder + "tile_" + std::to_string(tileCount) + ".png";
        
        while (std::filesystem::exists(foregroundPath)) {
            std::cout << "Loading foreground texture: " << foregroundPath<< std::endl;
            _foregroundTextures.emplace_back();
            _foregroundTextures.back().loadFromFile(foregroundPath);
            _foregroundSprites.emplace_back(sf::Sprite(_foregroundTextures.back()));
            _foregroundSprites.back().setScale(sf::Vector2f(2.1f, 2.1f));
            _foregroundSprites.back().setPosition(static_cast<float>(columnCount * 2048 * 2.1f), static_cast<float>(rowCount * 2048 * 2.1f));

            columnCount++;
            if (columnCount >= _mapWidth) {
                columnCount = 0;
                rowCount++;
            }
            tileCount++;
            foregroundPath = foregroundFolder + "tile_" + std::to_string(tileCount) + ".png";
        }

        std::cout << "Map initialized with " << _size << " sprites (x2)." << std::endl;
    };

    Map::~Map()
    {
        _groundTextures.clear();
        _foregroundTextures.clear();
        _groundSprites.clear();
        _foregroundSprites.clear();
    }

    const sf::Sprite& Map::getGroundSpriteAt(const int& index) const
    {
        if (index < 0 || static_cast<size_t>(index) >= _groundSprites.size())
            throw std::out_of_range("Index out of range in Map::getGroundSpriteAt");
        return _groundSprites[index];
    }

    const sf::Sprite& Map::getForegroundSpriteAt(const int& index) const
    {
        if (index < 0 || static_cast<size_t>(index) >= _foregroundSprites.size())
            throw std::out_of_range("Index out of range in Map::getForegroundSpriteAt");
        return _foregroundSprites[index];
    }
}
