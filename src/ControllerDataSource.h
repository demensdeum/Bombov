#pragma once

#include "ControllerType.h"

namespace DemensDeum::Bombov {
class ControllerDataSource {
public:
    virtual std::shared_ptr<std::unordered_map<std::string, std::string>> globalsForController(ControllerType controllerType) = 0;
};
}