#include "Scene.h"

#include "MapGenerator.h"

namespace DemensDeum::Bombov {

Scene::Scene() {
    camera = std::make_shared<Camera>();
    camera->position->x = -2;
    camera->position->y = -0.5;
    camera->position->z = 4;
    map = MapGenerator::box(32, 32);
}

std::shared_ptr<Map> Scene::getMap() {
    return map;
}

std::shared_ptr<Camera> Scene::getCamera() {
    return camera;
}

}