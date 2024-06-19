#pragma once

namespace DemensDeum::Bombov {

typedef struct {
    bool exitFromGame = false;
    bool forward = false;
    bool back = false;
    bool left = false;
    bool right = false;
} PressedButtons;

}