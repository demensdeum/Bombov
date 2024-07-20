#include "MapGenerator.h"

namespace DemensDeum::Bombov {

std::shared_ptr<Map> MapGenerator::box(uint64_t width, uint64_t height) {

    auto map = std::make_shared<Map>(width, height);
    for (uint64_t y = 0; y < map->height; y++) {
        for (uint64_t x= 0; x < map->width; x++) {
            bool isSolid = x == 0 || y == 0 || x == map->width - 1 || y == map->height - 1;
            map->setSolid(isSolid, x, y);
        }
    }
    return map;
}

}