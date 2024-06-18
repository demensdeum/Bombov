#pragma once

#include "GraphicsApiType.h"
#include <SDL2/SDL.h>
#include "Render.h"

namespace DemensDeum::Bombov {

class SDLSystem {

public:
    static int screenWidth;
    static int screenHeight;
    static float screenAspect;

    void init(GraphicsApiType graphicsApiType);
    void pollEvents();

    std::shared_ptr<Render> render;

    SDL_Window *window;
    bool isRun;
};

}