#include <Controller.h>

namespace DemensDeum::Bombov {

Controller::Controller(const std::function<void()>& inputStepClosure)
    : stepClosure(inputStepClosure) {
}

void Controller::step() {
    stepClosure();
}

}