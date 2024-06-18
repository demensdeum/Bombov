#pragma once

namespace DemensDeum::Bombov {

class Vector3 {

public:
    Vector3();
    Vector3(float x, float y, float z);

    void normalize();

    float x;
    float y;
    float z;

};

}
