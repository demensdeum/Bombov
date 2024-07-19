#pragma once

#include <memory>
#include <Render.h>
#include <SDL2/SDL.h>

namespace DemensDeum::Bombov {

class BgfxRender: public Render {

public:
    void setWindow(SDL_Window *window) override;
    virtual void setScene(std::shared_ptr<DemensDeum::Bombov::Scene> scene) override;
    virtual void render() override;

private:
    std::shared_ptr<Scene> scene;
    SDL_Window *window;
};

}