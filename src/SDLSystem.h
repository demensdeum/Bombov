#pragma once

#include "GraphicsApiType.h"
#include <SDL2/SDL.h>

namespace DemensDeum::Bombov {

class SDLSystem {

public:
    void init(GraphicsApiType graphicsApiType);

    SDL_Window *window;
};

}