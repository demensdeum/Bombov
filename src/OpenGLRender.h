#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "Render.h"
#include <memory>
#include <vector>

namespace DemensDeum::Bombov {

class OpenGLRender: public Render {

public:
    OpenGLRender();
    void setWindow(SDL_Window *window);
    void setScene(std::shared_ptr<Scene> scene) override;
    void render() override;

private:

    typedef struct {
        GLfloat Position[3];
        GLfloat TextureUV[2];
    } Vertex;

    std::vector<Vertex> verticesVectorFromMap(std::shared_ptr<Map> map);

    void CheckCompileErrors(GLuint object, const std::string objectType);
    void CheckLinkErrors(GLint programID);

    std::shared_ptr<Scene> scene;
    SDL_Window *window;
};

}