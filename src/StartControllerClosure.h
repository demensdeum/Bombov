#include <memory>
#include "ControllerType.h"
#include "ControllerDelegate.h"
#include "ControllerDataSource.h"
#include <unordered_map>

namespace DemensDeum::Bombov {
auto startControllerClosure = [](
    ControllerType controllerType, 
    std::shared_ptr<ControllerDataSource> controllerDataSource, 
    std::shared_ptr<ControllerDelegate> controllerDelegate
) {
    std::print("Controller Closure Step\n");

    auto globals = controllerDataSource->globalsForController(controllerType);
    if (globals->contains("closeCounter")) {
        auto closeCounter = std::stoi((*globals)["closeCounter"]);
        closeCounter++;
        if (closeCounter > 200) {
            controllerDelegate->controllerDidRequestQuit(controllerType);
        }
        (*globals)["closeCounter"] = std::to_string(closeCounter);
    }
    else {
        (*globals)["closeCounter"] = "0";
    }

};
}