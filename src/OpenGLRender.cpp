#include "OpenGLRender.h"
#include <print>

namespace DemensDeum::Bombov {

OpenGLRender::OpenGLRender() {}

void OpenGLRender::setScene(std::shared_ptr<Scene> scene) {
    this->scene = scene;
}

void OpenGLRender::render() {
    std::print("OpenGLRender::render\n");
}

}