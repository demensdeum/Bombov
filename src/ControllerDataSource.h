#pragma once

#include "ControllerType.h"
#include "PressedButtons.h"

namespace DemensDeum::Bombov {
class ControllerDataSource {
public:
    virtual PressedButtons pressedButtonsForController(ControllerType controllerType) = 0;
    virtual std::shared_ptr<std::unordered_map<std::string, std::string>> globalsForController(ControllerType controllerType) = 0;
    virtual std::shared_ptr<Camera> cameraForController(ControllerType controllerType) = 0;
};
}