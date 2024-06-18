#pragma once

#include <memory>
#include "Camera.h"
#include "Map.h"

namespace DemensDeum::Bombov {

class Scene {

public:
    Scene();
    std::shared_ptr<Camera> getCamera();
    std::shared_ptr<Map> getMap();

private:
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Map> map;

};

}