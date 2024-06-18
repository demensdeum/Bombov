#include "Scene.h"

namespace DemensDeum::Bombov {

Scene::Scene() {
    camera = std::make_shared<Camera>();

    camera->position->y = 2.f;

    map = std::make_shared<Map>(64, 64);
}

std::shared_ptr<Map> Scene::getMap() {
    return map;
}

std::shared_ptr<Camera> Scene::getCamera() {
    return camera;
}

}