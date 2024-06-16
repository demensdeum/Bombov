#pragma once

#include <memory>
#include "Scene.h"

namespace DemensDeum::Bombov {

class Render {

public:
    virtual void setScene(std::shared_ptr<DemensDeum::Bombov::Scene> scene) const = 0;
    virtual void render() const = 0;
};

}