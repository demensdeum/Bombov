#pragma once

#include <GL/glew.h>
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

    void CheckCompileErrors(GLuint object, const std::string objectType);
    void CheckLinkErrors(GLint programID);

    std::shared_ptr<Scene> scene;
    SDL_Window *window;
};

}