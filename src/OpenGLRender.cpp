#include "OpenGLRender.h"
#include <print>
#include <GL/glew.h>

namespace DemensDeum::Bombov {

OpenGLRender::OpenGLRender() {}

void OpenGLRender::setWindow(SDL_Window *window) {
    this->window = window;
}

void OpenGLRender::setScene(std::shared_ptr<Scene> scene) {
    this->scene = scene;
}

void OpenGLRender::render() {
    std::print("OpenGLRender::render\n");

    glClearColor(0.2f, 0.35f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
}

}