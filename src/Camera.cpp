#include "Camera.h"

namespace DemensDeum::Bombov {

Camera::Camera() {
    position = std::make_shared<Vector3>();
    rotation = std::make_shared<Vector3>();
}

std::shared_ptr<Matrix4> Camera::viewMatrix() {
    auto matrix = std::make_shared<Matrix4>();
    matrix->translate(position->x, position->y, position->z);
    matrix->rotate(rotation->x, Vector3(1.f, 0.f, 0.f));
    matrix->rotate(rotation->y, Vector3(0.f, 1.f, 0.f));
    matrix->rotate(rotation->z, Vector3(0.f, 0.f, 1.f));
    return matrix;
}

}