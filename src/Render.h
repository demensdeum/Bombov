#pragma once

#include <memory>
#include "Scene.h"

namespace DemensDeum::Bombov {

class Render {

public:
    virtual void setScene(std::shared_ptr<DemensDeum::Bombov::Scene> scene) = 0;
    virtual void render() = 0;
};

}