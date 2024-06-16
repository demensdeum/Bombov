#pragma once

#include <memory>
#include <unordered_map>
#include "ControllerType.h"
#include "Controller.h"
#include "ControllerDataSource.h"
#include "ControllerDelegate.h"

namespace DemensDeum::Bombov {

class Context: public ControllerDataSource, public ControllerDelegate {

public:
    Context(std::shared_ptr<bool>isRun);
    void step();
    void setController(ControllerType controllerType, std::shared_ptr<Controller> controller);
    void switchCurrentController(ControllerType controllerType);

    void controllerDidRequestQuit(ControllerType controllerType);

private:
    std::unordered_map<ControllerType, std::shared_ptr<Controller>> controllers;
    std::shared_ptr<Controller> currentController;

    std::shared_ptr<bool> isRun;
};

}