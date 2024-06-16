#include <iostream>
#include <print> 
#include <memory>
#include "Context.h"
#include "ControllerType.h"
#include "ControllersClosures.h"

using namespace DemensDeum::Bombov;

int main(int argc, char **argv) {
 
    std::print("Hello Bombov!\n");

    auto isRun = std::make_shared<bool>(true);

    auto context = std::make_shared<Context>(isRun);
    auto startController = std::make_shared<Controller>(
        InGameController,
        context,
        context,
        startControllerClosure
    );
    context->setController(InGameController, startController);
    context->switchCurrentController(InGameController);

    while (*isRun) {
        context->step();
    }

    std::print("Bye Bombov!\n");
}