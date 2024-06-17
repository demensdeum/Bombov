#pragma once

#include <SDL2/SDL.h>
#include "Render.h"

namespace DemensDeum::Bombov {

class OpenGLRender: public Render {

public:
    OpenGLRender();
    void setWindow(SDL_Window *window);
    void setScene(std::shared_ptr<Scene> scene) override;
    void render() override;

private:
    std::shared_ptr<Scene> scene;
    SDL_Window *window;

};

}