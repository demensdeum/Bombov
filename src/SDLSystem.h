#pragma once

#include "GraphicsApiType.h"
#include <SDL2/SDL.h>
#include "Render.h"
#include "PressedButtons.h"

namespace DemensDeum::Bombov {

class SDLSystem {

public:
    static uint screenWidth;
    static uint screenHeight;
    static float screenAspect;

    void init(GraphicsApiType graphicsApiType);
    void pollEvents();

    void quit();

    std::shared_ptr<Render> render;

    SDL_Window *window;

    PressedButtons pressedButtons;

private:
    void initializeOpenGL();
    void initializeVulkan();
};

}