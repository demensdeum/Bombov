#include <memory>
#include "ControllerType.h"
#include "ControllerDelegate.h"
#include "ControllerDataSource.h"
#include <unordered_map>
#include <print>

namespace DemensDeum::Bombov {
auto startControllerClosure = [](
    ControllerType controllerType, 
    std::shared_ptr<ControllerDataSource> controllerDataSource, 
    std::shared_ptr<ControllerDelegate> controllerDelegate
) {
    auto camera = controllerDataSource->cameraForController(controllerType);
    camera->position->z += 0.05;
};
}