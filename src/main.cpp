#include <iostream>
#include <print> 
#include <memory>
#include "OpenGLRender.h"
#include "Context.h"
#include "ControllerType.h"
#include "StartControllerClosure.h"
#include "SDLSystem.h"

using namespace DemensDeum::Bombov;

int main(int argc, char **argv) {
 
    std::print("Hello Bombov!\n");

    auto system = std::make_shared<SDLSystem>();
    system->init(OpenGL);

    auto isRun = std::make_shared<bool>(true);
    auto render = std::make_shared<OpenGLRender>();
    render->setWindow(system->window);

    auto context = std::make_shared<Context>(render, isRun);
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