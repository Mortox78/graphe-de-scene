#include <iostream>
#include <assert.h>
#include <cmath>
#include "matrix.h"
#include "matrix4.h"
#include "Vec3.h"
#include <vector>
#include <assert.h>

Matrix4::Matrix4()
{
    array.resize(16, 0.f);
    n = 4;
    m = 4;
}

Matrix4::~Matrix4()
{

}

Matrix4::Matrix4(const Matrix& mat)
{
    assert(mat.n == 4 && mat.m == 4);
    array.resize(16, 0.f);
    n = 4;
    m = 4;
    array = mat.array;
}

Matrix4 Matrix4::CreateScaleMatrix(const Vec3& vec3)
{
    Matrix4 matScale;

    matScale.accessor(0, 0) = vec3.x;
    matScale.accessor(1, 1) = vec3.y;
    matScale.accessor(2, 2) = vec3.z;
    matScale.accessor(3, 3) = 1;

    return matScale;
}

Matrix4 Matrix4::CreateTranslationMatrix(const Vec3& vec3)
{
    Matrix4 matTranslate = Matrix4::identity(4);

    matTranslate.accessor(0, 3) = vec3.x;
    matTranslate.accessor(1, 3) = vec3.y;
    matTranslate.accessor(2, 3) = vec3.z;

    return matTranslate;
}

Matrix4 Matrix4::CreateXRotationMatrix(const float& angleX)
{
    Matrix4 matRotateX = Matrix4::identity(4);

    matRotateX.accessor(1, 1) = cos(angleX);
    matRotateX.accessor(1, 2) = -sin(angleX);
    matRotateX.accessor(2, 1) = sin(angleX);
    matRotateX.accessor(2, 2) = cos(angleX);

    return matRotateX;
}

Matrix4 Matrix4::CreateYRotationMatrix(const float& angleY)
{
    Matrix4 matRotateY = Matrix4::identity(4);

    matRotateY.accessor(0, 0) = cos(angleY);
    matRotateY.accessor(0, 2) = sin(angleY);
    matRotateY.accessor(2, 0) = -sin(angleY);
    matRotateY.accessor(2, 2) = cos(angleY);

    return matRotateY;
}

Matrix4 Matrix4::CreateZRotationMatrix(const float& angleZ)
{
    Matrix4 matRotateZ = Matrix4::identity(4);

    matRotateZ.accessor(0, 0) = cos(angleZ);
    matRotateZ.accessor(0, 1) = -sin(angleZ);
    matRotateZ.accessor(1, 0) = sin(angleZ);
    matRotateZ.accessor(1, 1) = cos(angleZ);

    return matRotateZ;
}

// vec3 contains the angles that we need in order to create the matrix rotation
Matrix4 Matrix4::CreateFixedAngleEulerRotationMatrix(const Vec3& vec3)
{
    Matrix matRotX = CreateXRotationMatrix(vec3.x);
    Matrix matRotY = CreateYRotationMatrix(vec3.y);
    Matrix matRotZ = CreateZRotationMatrix(vec3.z);

    return matRotY * matRotX * matRotZ;
}

Matrix4 Matrix4::CreateTRSMatrix(const Vec3& scale, const Vec3& rotation, const Vec3& translation)
{
    Matrix4 matT = CreateTranslationMatrix(translation);
    Matrix4 matR = CreateFixedAngleEulerRotationMatrix(rotation);
    Matrix4 matS = CreateScaleMatrix(scale);

    Matrix4 matRS = matR * matS;

    return matT * matRS;
}


Matrix4 operator*(const Matrix4& mat1, float factor)
{
    assert(factor != 0 && mat1.n == 4 && mat1.m == 4);
    Matrix4 newMatrix;

    for (int i = 0; i < newMatrix.n * newMatrix.m; ++i)
    {
        newMatrix.array[i] = mat1.array[i] * factor;
    }
    
    return newMatrix;
}


Vec4 operator*(Matrix4& mat1, const Vec4& vecToMultiply)
{
    Matrix4 vec4casted;
    vec4casted.accessor(0, 0) = vecToMultiply.x;
    vec4casted.accessor(1, 0) = vecToMultiply.y;
    vec4casted.accessor(2, 0) = vecToMultiply.z;
    vec4casted.accessor(3, 0) = vecToMultiply.w;

    Matrix4 result = mat1 * vec4casted;

    return Vec4(result.accessor(0, 0), result.accessor(1, 0), result.accessor(2, 0), result.accessor(3, 0));
}