#pragma once

#include <memory>
#include "Scene.h"
#include <SDL2/SDL.h>

namespace DemensDeum::Bombov {

class Render {

public:
    virtual void setWindow(SDL_Window *window) = 0;
    virtual void setScene(std::shared_ptr<DemensDeum::Bombov::Scene> scene) = 0;
    virtual void render() = 0;
};

}