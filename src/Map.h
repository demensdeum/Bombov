#pragma once

#include "Tile.h"
#include <vector>
#include <memory>

namespace DemensDeum::Bombov {
class Map {
public:
    Map(const uint width, const uint height);
    void setTile(std::shared_ptr<DemensDeum::Bombov::Tile> tile, const uint x, const uint y);
    std::shared_ptr<DemensDeum::Bombov::Tile> getTile(const uint x, const uint y);

    void setSolid(const bool isSolid, uint x, uint y);
    bool isSolid(const uint x, const uint y);

    const uint width;
    const uint height;

private:
    void guardBounds(const uint x, const uint y);
    std::vector<std::vector<std::shared_ptr<DemensDeum::Bombov::Tile>>> tiles;
};
};