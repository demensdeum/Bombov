#include "Context.h"
#include "Controller.h"
#include <print>

namespace DemensDeum::Bombov {

Context::Context(
    std::shared_ptr<SDLSystem> system,
    std::shared_ptr<bool>isRun
) : isRun(isRun), 
    system(system) {
        globals = std::make_shared<std::unordered_map<std::string, std::string>>();
        scene = std::make_shared<Scene>();
    }

void Context::setController(ControllerType controllerType, std::shared_ptr<Controller> controller) {
    controllers[controllerType] = controller;
}

void Context::controllerDidRequestQuit(ControllerType controllerType) {
    *isRun = !*isRun;
}

std::shared_ptr<std::unordered_map<std::string, std::string>> Context::globalsForController(ControllerType controllerType) {
    return this->globals;
}

std::shared_ptr<Camera> Context::cameraForController(ControllerType controllerType) {
    return scene->getCamera();
}

PressedButtons Context::pressedButtonsForController(ControllerType controllerType) {
    return system->pressedButtons;
}

void Context::switchCurrentController(
    ControllerType controllerType
) {
    if (!controllers.contains(controllerType)) {
        std::string exceptionString = std::string("No controller for controller type: ") + std::to_string(controllerType);
        throw std::runtime_error(exceptionString);
    }
    currentController = controllers[controllerType];
}

void Context::step() { 
    system->pollEvents();
    currentController->step();
    system->render->setScene(scene);
    system->render->render();
}

}