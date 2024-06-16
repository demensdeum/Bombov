#include <iostream>
#include "Map.h"
#include <print>

int main(int argc, char **argv) {
    auto map = new DemensDeum::Bombov::Map(256, 256);

    const uint x = 10;
    const uint y = 10;

    map->setSolid(false, x, y);

    std::cout << "Hello Bombov" << std::endl;

    if (!map->getTile(x, y)->isSolid()) {
        std::print("{0} {1} tile is not solid\n", x, y);
    }

}