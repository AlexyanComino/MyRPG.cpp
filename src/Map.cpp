
#include "Map.hpp"

namespace MyRpg {
    Map::Map(const std::string& groundFolder, const std::string& foregroundFolder, const int& mapWidth) : _mapWidth(mapWidth), _size(0)
    {
        int rowCount = 0;
        int columnCount = 0;

        std::cout << groundFolder << std::endl;
        
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
            _groundSprites.push_back(sf::Sprite(_groundTextures.back()));
            _groundSprites.back().setScale(sf::Vector2f(0.05f, 0.05f));
            _groundSprites.back().setPosition(static_cast<float>(columnCount * 1024 * 0.05f), static_cast<float>(rowCount * 1024 * 0.05f));
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
            _foregroundSprites.push_back(sf::Sprite(_foregroundTextures.back()));
            _foregroundSprites.back().setScale(sf::Vector2f(2.1f, 2.1f));
            _foregroundSprites.back().setPosition(static_cast<float>(columnCount * 1024 * 0.05f), static_cast<float>(rowCount * 1024 * 0.05f));

            columnCount++;
            if (columnCount >= _mapWidth) {
                columnCount = 0;
                rowCount++;
            }
            tileCount++;
            foregroundPath = foregroundFolder + "tile_" + std::to_string(tileCount) + ".png";
        }

        std::cout << "Map initialized with " << _size << " sprites." << std::endl;
    };

    Map::~Map()
    {
        _groundTextures.clear();
        _foregroundTextures.clear();
        _groundSprites.clear();
        _foregroundSprites.clear();
    }
}
