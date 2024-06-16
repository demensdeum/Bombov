#include <print>
#include "Map.h"

DemensDeum::Bombov::Map::Map(const uint width, const uint height): width(width), height(height) {
    for (uint y = 0; y < height; y ++) {
        std::vector<std::shared_ptr<DemensDeum::Bombov::Tile>> row;
        for (uint x = 0; x < width; x++) {
            auto tile = std::make_shared<DemensDeum::Bombov::Tile>();
            row.push_back(tile);
        }
        tiles.push_back(row);
    }
}

void DemensDeum::Bombov::Map::setSolid(const bool isSolid, uint x, uint y) {
    getTile(x, y)->setSolid(isSolid);
}

bool DemensDeum::Bombov::Map::isSolid(const uint x, const uint y) {
    return getTile(x, y)->isSolid();
}

void DemensDeum::Bombov::Map::guardBounds(const uint x, const uint y) {
    if (x >= width) {
        throw std::runtime_error("Map x >= width, wtf?");
    }
    if (y >= height) {
        throw std::runtime_error("Map y >= height, wtf?");
    }
}

void DemensDeum::Bombov::Map::setTile(std::shared_ptr<DemensDeum::Bombov::Tile> tile, const uint x, const uint y) {
    guardBounds(x, y);
    tiles[y][x] = tile;
}

std::shared_ptr<DemensDeum::Bombov::Tile> DemensDeum::Bombov::Map::getTile(const uint x, const uint y) {
    guardBounds(x, y);
    return tiles[y][x];
}
