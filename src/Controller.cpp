#include <Controller.h>

namespace DemensDeum::Bombov {

Controller::Controller(
        DemensDeum::Bombov::ControllerType controllerType,
        std::shared_ptr<ControllerDataSource> dataSource,
        std::shared_ptr<ControllerDelegate> delegate,
        const std::function<void(ControllerType controllerType, std::shared_ptr<ControllerDataSource> controllerDataSource, std::shared_ptr<ControllerDelegate> controllerDelegate)>& inputStepClosure
    )
    : controllerType(controllerType), dataSource(dataSource), delegate(delegate), stepClosure(inputStepClosure) {
}

void Controller::step() {
    stepClosure(controllerType, dataSource, delegate);
}

}