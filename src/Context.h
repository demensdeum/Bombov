#pragma once

#include <memory>
#include <unordered_map>
#include "ControllerType.h"
#include "Controller.h"

namespace DemensDeum::Bombov {

class Controller;

class Context {

public:
    Context(std::shared_ptr<bool>isRun, std::shared_ptr<DemensDeum::Bombov::Controller> currentController);
    void step();

private:
    std::unordered_map<Demensdeum::Bombov::ControllerType, DemensDeum::Bombov::Controller> controllers;
    std::shared_ptr<DemensDeum::Bombov::Controller> currentController;

    std::shared_ptr<bool> isRun;
};

}