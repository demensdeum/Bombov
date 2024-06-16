#pragma mark once

#include <memory>
#include <Vector3.h>
#include <Quaternion.h>

namespace DemensDeum::Bombov {
class Object {

private:
    std::shared_ptr<Vector3> position;
    std::shared_ptr<Quaternion> rotation;

};
}