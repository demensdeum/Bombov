#include "Context.h"
#include "Controller.h"
#include <print>

namespace DemensDeum::Bombov {

Context::Context(std::shared_ptr<bool>isRun, std::shared_ptr<DemensDeum::Bombov::Controller> currentController) : isRun(isRun), currentController(currentController) {

}

void Context::step() { 
    std::print("Context step\n");
    currentController->step();
}

}