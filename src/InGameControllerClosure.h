#include <memory>
#include "ControllerType.h"
#include "ControllerDelegate.h"
#include "ControllerDataSource.h"
#include <unordered_map>
#include <print>

namespace DemensDeum::Bombov {
auto inGameControllerClosure = [](
    ControllerType controllerType, 
    std::shared_ptr<ControllerDataSource> controllerDataSource, 
    std::shared_ptr<ControllerDelegate> controllerDelegate
) {
    auto camera = controllerDataSource->cameraForController(controllerType);
    auto pressedButtons = controllerDataSource->pressedButtonsForController(controllerType);

    float yaw = camera->rotation->y * (3.14159265f / 180.0f);

    float forwardX = sin(yaw);
    float forwardZ = cos(yaw);
    float rightX = cos(yaw);
    float rightZ = -sin(yaw);

    if (pressedButtons.forward) {
        camera->position->x += forwardX * 0.05f;
        camera->position->z += forwardZ * 0.05f;
    }
    if (pressedButtons.back) {
        camera->position->x -= forwardX * 0.05f;
        camera->position->z -= forwardZ * 0.05f;
    }

    if (pressedButtons.left) {
        camera->rotation->y += 1.f;  // Поворот камеры влево
    }
    if (pressedButtons.right) {
        camera->rotation->y -= 1.f;  // Поворот камеры вправо
    }

    // strafe
    // if (pressedButtons.left) {
    //     camera->position->x -= rightX * 0.05f;
    //     camera->position->z -= rightZ * 0.05f;
    // }
    // if (pressedButtons.right) {
    //     camera->position->x += rightX * 0.05f;
    //     camera->position->z += rightZ * 0.05f;
    // }
};
}
