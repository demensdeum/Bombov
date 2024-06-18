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
    auto globals = controllerDataSource->globalsForController(controllerType);
    if (globals->contains("closeCounter")) {
        auto closeCounter = std::stoi((*globals)["closeCounter"]);
        closeCounter++;
        std::print("closeCounter: {0}\n", closeCounter);
        if (closeCounter > 100) {
            controllerDelegate->controllerDidRequestQuit(controllerType);
        }
        (*globals)["closeCounter"] = std::to_string(closeCounter);
    }
    else {
        (*globals)["closeCounter"] = "0";
    }

};
}