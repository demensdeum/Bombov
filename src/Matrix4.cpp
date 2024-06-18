#include "Matrix4.h"
#include <iostream>
#include <Vector3.h>

#include <cmath>

#if BOMBOV_GAME_GLM_ENABLED
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace DemensDeum::Bombov {

Matrix4::Matrix4() {
    this->becomeUnit();
}

void* Matrix4::glRepresentation() {
#if BOMBOV_GAME_GLM_ENABLED
    return glm::value_ptr(matrix);
#else
    return matrix.data();
#endif
}

void Matrix4::translate(float x, float y, float z) {
#if BOMBOV_GAME_GLM_ENABLED
    matrix = glm::translate(matrix, glm::vec3(x, y, z));
#else
    Matrix4 translationMatrix;
    translationMatrix.becomeUnit();

    translationMatrix.matrix[12] = x;
    translationMatrix.matrix[13] = y;
    translationMatrix.matrix[14] = z;

    *this = *this * translationMatrix;    
#endif
}

void Matrix4::rotate(float angle, Vector3 axis) {
#if BOMBOV_GAME_GLM_ENABLED
    glm::vec3 glmAxis(axis.x, axis.y, axis.z);
    matrix = glm::rotate(matrix, angle, glmAxis);
#else
    float rad = angle * (M_PI / 180.0f);
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);
    float oneMinusCosA = 1.0f - cosA;

    axis.normalize();
    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    Matrix4 rotationMatrix;
    rotationMatrix.matrix = {
        cosA + x * x * oneMinusCosA,     x * y * oneMinusCosA - z * sinA, x * z * oneMinusCosA + y * sinA, 0,
        y * x * oneMinusCosA + z * sinA, cosA + y * y * oneMinusCosA,     y * z * oneMinusCosA - x * sinA, 0,
        z * x * oneMinusCosA - y * sinA, z * y * oneMinusCosA + x * sinA, cosA + z * z * oneMinusCosA,     0,
        0,                              0,                              0,                              1
    };

    *this = *this * rotationMatrix;
#endif
}

Matrix4& Matrix4::operator=(const Matrix4& other) {
    if (this != &other) {
        this->matrix = other.matrix;
    }
    return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {
#if BOMBOV_GAME_GLM_ENABLED
    glm::mat4 glmMatrixResult = matrix * other.matrix;
    Matrix4 resultMatrix;
    resultMatrix.matrix = glmMatrixResult;
    return resultMatrix;
#else
    Matrix4 result;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result.matrix[row * 4 + col] = 
                matrix[row * 4 + 0] * other.matrix[0 * 4 + col] +
                matrix[row * 4 + 1] * other.matrix[1 * 4 + col] +
                matrix[row * 4 + 2] * other.matrix[2 * 4 + col] +
                matrix[row * 4 + 3] * other.matrix[3 * 4 + col];
        }
    }

    return result;
#endif
}

void Matrix4::becomePerspective(float fov, float aspect, float near, float far) {
#if BOMBOV_GAME_GLM_ENABLED
    matrix = glm::perspective(fov, aspect, near, far);
#else
    float tanHalfFov = std::tan(fov / 2.0f * (M_PI / 180.0f));

    matrix = {
        1.0f / (aspect * tanHalfFov), 0, 0, 0,
        0, 1.0f / tanHalfFov, 0, 0,
        0, 0, -(far + near) / (far - near), -1,
        0, 0, -(2 * far * near) / (far - near), 0
    };
#endif
}

void Matrix4::becomeUnit() {
#if BOMBOV_GAME_GLM_ENABLED
    matrix = glm::mat4(1.f);
#else
        matrix = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        };
#endif
}

}