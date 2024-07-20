#pragma once

#include "Tile.h"
#include <vector>
#include <memory>

namespace DemensDeum::Bombov {
class Map {
public:
    Map(const uint64_t width, const uint64_t height);
    void setTile(std::shared_ptr<DemensDeum::Bombov::Tile> tile, const uint64_t x, const uint64_t y);
    std::shared_ptr<DemensDeum::Bombov::Tile> getTile(const uint64_t x, const uint64_t y);

    void setSolid(const bool isSolid, uint64_t x, uint64_t y);
    bool isSolid(const uint64_t x, const uint64_t y);

    const uint64_t width;
    const uint64_t height;

private:
    void guardBounds(const uint64_t x, const uint64_t y);
    std::vector<std::vector<std::shared_ptr<DemensDeum::Bombov::Tile>>> tiles;
};
};