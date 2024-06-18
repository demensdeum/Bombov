#include "Matrix4.h"
#include <iostream>
#include <Vector3.h>

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace DemensDeum::Bombov {

Matrix4::Matrix4() {
    this->becomeUnit();
}

void* Matrix4::glRepresentation() {
    return values.data();
}

void Matrix4::translate(float x, float y, float z) {
    Matrix4 translationMatrix;
    translationMatrix.becomeUnit();
    translationMatrix.values[12] = x;
    translationMatrix.values[13] = y;
    translationMatrix.values[14] = z;

    *this = *this * translationMatrix;
}

void Matrix4::rotate(float angle, Vector3 axis) {
    float rad = angle * (M_PI / 180.0f);
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);
    float oneMinusCosA = 1.0f - cosA;

    axis.normalize();
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    Matrix4 rotationMatrix;
    rotationMatrix.values = {
        cosA + x * x * oneMinusCosA,     x * y * oneMinusCosA - z * sinA, x * z * oneMinusCosA + y * sinA, 0,
        y * x * oneMinusCosA + z * sinA, cosA + y * y * oneMinusCosA,     y * z * oneMinusCosA - x * sinA, 0,
        z * x * oneMinusCosA - y * sinA, z * y * oneMinusCosA + x * sinA, cosA + z * z * oneMinusCosA,     0,
        0,                              0,                              0,                              1
    };

    *this = *this * rotationMatrix;
}

Matrix4& Matrix4::operator=(const Matrix4& other) {
    if (this != &other) {
        this->values = other.values;
    }
    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.values[row * 4 + col] = 
                values[row * 4 + 0] * other.values[0 * 4 + col] +
                values[row * 4 + 1] * other.values[1 * 4 + col] +
                values[row * 4 + 2] * other.values[2 * 4 + col] +
                values[row * 4 + 3] * other.values[3 * 4 + col];
        }
    }

    return result;
}

void Matrix4::becomePerspective(float fov, float aspect, float near, float far) {
    float tanHalfFov = std::tan(fov / 2.0f * (M_PI / 180.0f));

    values = {
        1.0f / (aspect * tanHalfFov), 0, 0, 0,
        0, 1.0f / tanHalfFov, 0, 0,
        0, 0, -(far + near) / (far - near), -1,
        0, 0, -(2 * far * near) / (far - near), 0
    };
}

void Matrix4::becomeUnit() {
        values = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
}

}