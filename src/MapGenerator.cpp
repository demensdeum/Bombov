#include "MapGenerator.h"

namespace DemensDeum::Bombov {

std::shared_ptr<Map> MapGenerator::box(uint width, uint height) {

    auto map = std::make_shared<Map>(width, height);
    for (uint y = 0; y < map->height; y++) {
        for (uint x= 0; x < map->width; x++) {
            bool isSolid = x == 0 || y == 0 || x == map->width - 1 || y == map->height - 1;
            map->setSolid(isSolid, x, y);
        }
    }
    return map;
}

}