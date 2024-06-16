#pragma once

#include <memory>
#include <Camera.h>

namespace DemensDeum::Bombov {

class Scene {

public:
    std::shared_ptr<DemensDeum::Bombov::Camera> getCamera();

};

}