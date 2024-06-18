#pragma once

#include <memory>
#include <Vector3.h>
#include <Quaternion.h>
#include <Matrix4.h>

namespace DemensDeum::Bombov {
class Camera {

public:
    std::shared_ptr<Matrix4> viewMatrix();

private:
    std::shared_ptr<DemensDeum::Bombov::Vector3> position;
    std::shared_ptr<DemensDeum::Bombov::Quaternion> rotation;
    std::shared_ptr<DemensDeum::Bombov::Matrix4> projection;
};
}