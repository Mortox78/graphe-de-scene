#include <iostream>
#include <math.h>
#include "Vec4.h"
#include "Vec3.h"


Vec4::Vec4()
{

}

Vec4::~Vec4()
{

}

Vec4::Vec4(const Vec3& vec3)
{
    x = vec3.x;
    y = vec3.y;
    z = vec3.z;
    w = 1.f;
}


Vec4::Vec4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

void Vec4::Homogenize()
{
    if (w != 0)
    {
        x /= w;
        y /= w;
        z /= w;
    }
}

float Vec4::GetMagnitude() const
{
    return sqrt((x * x) + (y * y) + (z * z));
}

void Vec4::Normalize()
{
    float magnitude = GetMagnitude();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}


Vec4 operator+(Vec4 v1, Vec4 v2)
{
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
}


Vec4 operator*(Vec4 v1, Vec4 v2)
{
    return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w};
}