#pragma once

#include <functional>
#include "Scene.h"
#include <memory>

namespace DemensDeum::Bombov {

class Controller {
public:
    Controller(const std::function<void()>& inputStepClosure);
    void step();

private:
    const std::function<void()> stepClosure;
};

}