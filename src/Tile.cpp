#include <Tile.h>

DemensDeum::Bombov::Tile::Tile(bool isSolid) {
    this->solid = isSolid;
}

void DemensDeum::Bombov::Tile::setSolid(bool isSolid) {
    this->solid = isSolid;
}

bool DemensDeum::Bombov::Tile::isSolid() {
    return this->solid;
}
