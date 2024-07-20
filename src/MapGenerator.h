#pragma once

#include <memory>
#include "Map.h"

namespace DemensDeum::Bombov {

class MapGenerator {

public:
    static std::shared_ptr<Map> box(uint64_t width, uint64_t height);

};

}