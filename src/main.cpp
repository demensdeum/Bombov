#include <iostream>
#include "Map.h"

int main(int argc, char **argv) {
    auto map = new DemensDeum::Bambov::Map();
    map->hello();
    std::cout << "Hello Bombov" << std::endl;
}