#pragma once

#include "GraphicsApiType.h"
#include <SDL2/SDL.h>

namespace DemensDeum::Bombov {

class SDLSystem {

public:
    static int screenWidth;
    static int screenHeight;
    static float screenAspect;

    void init(GraphicsApiType graphicsApiType);

    SDL_Window *window;
};

}