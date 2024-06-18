#pragma once

#include <array>
#include "Vector3.h"
#include "Options.h"

#if BOMBOV_GAME_GLM_ENABLED
#include <glm/mat4x4.hpp>
#endif

namespace DemensDeum::Bombov {

class Matrix4 {

public:
    Matrix4();
    void* glRepresentation();
    void becomeUnit();
    void becomePerspective(float fov, float aspect, float near, float far);
    void translate(float x, float y, float z);
    void rotate(float angle, Vector3 axis);

    Matrix4& operator=(const Matrix4& other);
    Matrix4 operator*(const Matrix4& other) const;

private:
#if BOMBOV_GAME_GLM_ENABLED
    glm::mat4 matrix;
#else
    std::array<float, 4 * 4> matrix;
#endif

};

}