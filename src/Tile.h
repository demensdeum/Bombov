#pragma once

namespace DemensDeum::Bombov {
class Tile {
public:
    Tile(bool isSolid = true);
    void setSolid(bool isSolid);
    bool isSolid();

private:
    bool solid;
};
}