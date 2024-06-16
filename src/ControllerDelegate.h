#pragma once

#include "ControllerType.h"

namespace DemensDeum::Bombov {
class ControllerDelegate {
public:
    virtual void controllerDidRequestQuit(DemensDeum::Bombov::ControllerType controllerType) = 0;
};
}