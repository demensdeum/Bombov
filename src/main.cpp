#include <iostream>
#include <print> 
#include <memory>
#include <chrono>
#include "OpenGLRender.h"
#include "Context.h"
#include "ControllerType.h"
#include "InGameControllerClosure.h"
#include "SDLSystem.h"
#include "Options.h"

using namespace DemensDeum::Bombov;

int main(int argc, char **argv) {
    constexpr int FPS = 60;
    constexpr std::chrono::milliseconds frameDuration(1000 / FPS);

    std::print("Hello Bombov!\n");

    auto system = std::make_shared<SDLSystem>();
    system->init(BOMBOV_GAME_GRAPHICS_API);

    auto isRun = std::make_shared<bool>(true);

    auto context = std::make_shared<Context>(system, isRun);
    auto startController = std::make_shared<Controller>(
        InGameController,
        context,
        context,
        inGameControllerClosure
    );
    context->setController(InGameController, startController);
    context->switchCurrentController(InGameController);

    auto lastTime = std::chrono::steady_clock::now();

    while (*isRun && !system->pressedButtons.exitFromGame) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime);

        if (elapsed >= frameDuration) {
            context->step();
            lastTime = currentTime;
        }
    }

    system->quit();
    std::print("Bye Bombov!\n");
}
