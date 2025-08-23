
#include "Collisions.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

namespace MyRpg {
    Collisions::Collisions(const std::string& collisionsFilePath) :
        rect(sf::IntRect(0, 0, static_cast<int>(TILE_SIZE), static_cast<int>(TILE_SIZE))), _size(0),
        _columns(static_cast<std::size_t>(((MAP_WIDTH + WIDTH + 1) * TILE_SCALE) / WIDTH)),
        _rows(static_cast<std::size_t>(((MAP_HEIGHT + HEIGHT + 1) * TILE_SCALE) / HEIGHT)),
        regions(createRegions(collisionsFilePath)),
        shape(sf::RectangleShape()), regionShape(sf::RectangleShape())
    {
        this->shape.setFillColor(sf::Color::Transparent);
        this->shape.setOutlineColor(sf::Color::Black);
        this->shape.setOutlineThickness(2);
        this->shape.setSize(sf::Vector2f(static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE)));

        this->regionShape.setFillColor(sf::Color::Transparent);
        this->regionShape.setOutlineColor(sf::Color::Red);
        this->regionShape.setOutlineThickness(2);
        this->regionShape.setSize(sf::Vector2f(WIDTH, HEIGHT));
    }

    std::vector<std::vector<region_t>> Collisions::createRegions(const std::string& collisionsFilePath)
    {
        _columns = static_cast<std::size_t>(((MAP_WIDTH + WIDTH + 1) * TILE_SCALE) / WIDTH);
        _rows = static_cast<std::size_t>(((MAP_HEIGHT + HEIGHT + 1) * TILE_SCALE) / HEIGHT);
        std::vector<std::vector<region_t>> newRegions(_columns, std::vector<region_t>(_rows));
        std::size_t column = 0;
        std::size_t row = 0;

        for (unsigned int i = 0; i < _columns; ++i)
            for (unsigned int j = 0; j < _rows; ++j)
                newRegions[i][j].rect = sf::IntRect(i * WIDTH, j * HEIGHT, WIDTH, HEIGHT);

        std::ifstream file(collisionsFilePath);
        std::string line;

        while (std::getline(file, line)) {
            char* cstr = const_cast<char*>(line.c_str());
            char* context = nullptr;
            float x = static_cast<float>(std::atoi(strtok_r(cstr, " ", &context)) * TILE_SCALE + TILE_SIZE * 12 - TILE_SIZE / 2);
            float y = static_cast<float>(std::atoi(strtok_r(nullptr, " ", &context)) * TILE_SCALE + TILE_SIZE / 2);

            column = x / WIDTH;
            row = y / HEIGHT;
            if (column > _columns || row > _rows)
                continue;
            newRegions[column][row].positions.push_back(sf::Vector2f(x, y));
            newRegions[column][row].size++;
        }

        return newRegions;
    }

    bool Collisions::checkRegion(const sf::IntRect hitbox, std::size_t col, std::size_t row)
    {
        if (col < 0 || row < 0 || col > _columns || row > _rows)
            return false;
        
        for (std::size_t i = 0; i < regions[col][row].size; i++) {
            this->rect.left = regions[col][row].positions[i].x;
            this->rect.top = regions[col][row].positions[i].y;
            if (hitbox.intersects(this->rect))
                return true;
        }
        return false;
    }

    bool Collisions::isIntRectCollidingWithMap(const sf::IntRect hitbox)
    {
        std::size_t col = hitbox.left / WIDTH;
        std::size_t row = hitbox.top / HEIGHT;

        if (col > _columns || row > _rows)
            return false;

        if (checkRegion(hitbox, col, row) ||
            checkRegion(hitbox, col, row + 1) ||
            checkRegion(hitbox, col, row - 1) ||
            checkRegion(hitbox, col + 1, row) ||
            checkRegion(hitbox, col + 1, row + 1) ||
            checkRegion(hitbox, col + 1, row - 1) ||
            checkRegion(hitbox, col - 1, row) ||
            checkRegion(hitbox, col - 1, row + 1) ||
            checkRegion(hitbox, col - 1, row - 1))
            return true;
        this->rect.left = 0;
        this->rect.top = 0;
        return false;
    }
}
