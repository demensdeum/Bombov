#pragma once

#include <memory>
#include "Map.h"

namespace DemensDeum::Bombov {

class MapGenerator {

public:
    static std::shared_ptr<Map> box(uint width, uint height);

};

}