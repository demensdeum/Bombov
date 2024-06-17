#pragma once

#include <memory>
#include <unordered_map>
#include "Render.h"
#include "ControllerType.h"
#include "Controller.h"
#include "ControllerDataSource.h"
#include "ControllerDelegate.h"

namespace DemensDeum::Bombov {

class Context: public ControllerDataSource, public ControllerDelegate {

public:
    Context(
        std::shared_ptr<Render> render,
        std::shared_ptr<bool> isRun
    );
    void step();
    void setController(ControllerType controllerType, std::shared_ptr<Controller> controller);
    void switchCurrentController(ControllerType controllerType);

    void controllerDidRequestQuit(ControllerType controllerType);
    std::shared_ptr<std::unordered_map<std::string, std::string>> globalsForController(ControllerType controllerType) override;

private:
    std::unordered_map<ControllerType, std::shared_ptr<Controller>> controllers;
    std::shared_ptr<Controller> currentController;

    std::shared_ptr<bool> isRun;
    std::shared_ptr<Render> render;
    std::shared_ptr<std::unordered_map<std::string, std::string>> globals;
};

}