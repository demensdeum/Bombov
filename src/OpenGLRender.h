#pragma once

#include "Render.h"

namespace DemensDeum::Bombov {

class OpenGLRender: public Render {

public:
    OpenGLRender();
    void setScene(std::shared_ptr<Scene> scene) override;
    void render() override;

private:
    std::shared_ptr<Scene> scene;

};

}