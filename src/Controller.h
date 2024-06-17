#pragma once

#include <functional>
#include "Scene.h"
#include <memory>
#include "ControllerType.h"
#include "ControllerDataSource.h"
#include "ControllerDelegate.h"

namespace DemensDeum::Bombov {

class Controller {
public:
    Controller(
        DemensDeum::Bombov::ControllerType controllerType,
        std::shared_ptr<ControllerDataSource> dataSource,
        std::shared_ptr<ControllerDelegate> delegate,
        const std::function<void(DemensDeum::Bombov::ControllerType controllerType, std::shared_ptr<ControllerDataSource> controllerDataSource, std::shared_ptr<ControllerDelegate> controllerDelegate)>& inputStepClosure
    );
    void step();

private:
    DemensDeum::Bombov::ControllerType controllerType;
    std::shared_ptr<std::unordered_map<std::string, std::string>> globals;
    std::shared_ptr<ControllerDataSource> dataSource;
    std::shared_ptr<ControllerDelegate> delegate;
    const std::function<void(DemensDeum::Bombov::ControllerType controllerType, std::shared_ptr<ControllerDataSource> controllerDataSource, std::shared_ptr<ControllerDelegate> controllerDelegate)> stepClosure;
};

}