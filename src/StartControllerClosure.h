#include <memory>
#include <ControllerType.h>
#include <ControllerDelegate.h>
#include <ControllerDataSource.h>

namespace DemensDeum::Bombov {
auto startControllerClosure = [](
    ControllerType controllerType, 
    std::shared_ptr<ControllerDataSource> controllerDataSource, 
    std::shared_ptr<ControllerDelegate> controllerDelegate
) {
    std::print("Controller Closure Step\n");
    controllerDelegate->controllerDidRequestQuit(controllerType);
};
}