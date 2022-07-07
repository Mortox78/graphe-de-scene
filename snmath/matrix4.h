#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "matrix.h"
#include "Vec3.h"
#include "Vec4.h"

class Matrix4 : public Matrix
{
    public:
    
    Matrix4();
    Matrix4(const Matrix& mat);
    ~Matrix4();

    static Matrix4 CreateScaleMatrix(const Vec3& vec3);
    static Matrix4 CreateTranslationMatrix(const Vec3& vec3);
    static Matrix4 CreateXRotationMatrix(const float& angleX);
    static Matrix4 CreateYRotationMatrix(const float& angleY);
    static Matrix4 CreateZRotationMatrix(const float& angleZ);
    static Matrix4 CreateFixedAngleEulerRotationMatrix(const Vec3& vec3);
    static Matrix4 CreateTRSMatrix(const Vec3& scale, const Vec3& rotation, const Vec3& translation);
};

Matrix4 operator*(const Matrix4& mat1, float factor);

Vec4 operator* (Matrix4& mat1, const Vec4& vecToMultiply);

#endif