#include <iostream>
#include <print> 
#include <memory>
#include "Context.h"

int main(int argc, char **argv) {
 
    std::print("Hello Bombov!\n");

    auto isRun = std::make_shared<bool>(true);

    auto startControllerClosure = []() {
        std::print("Controller Closure Step\n");
    };

    auto startController = std::make_shared<DemensDeum::Bombov::Controller>(startControllerClosure);
    auto context = std::make_shared<DemensDeum::Bombov::Context>(isRun, startController);

    while (isRun) {
        context->step();
    }

    std::print("Bye Bombov!\n");
}