#include <iostream>
#include <math.h>
#include "Vec3.h"
#include "Vec4.h"

Vec3::Vec3()
{

}

Vec3::Vec3(const float& x, const float& y, const float& z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vec3::Vec3(const Vec4& copyVec)
{
    this->x = copyVec.x;
    this->y = copyVec.y;
    this->z = copyVec.z;
}

Vec3::~Vec3()
{

}

float Vec3::GetMagnitude() const
{
    return sqrt((x * x) + (y * y) + (z * z));
}

void Vec3::Normalize()
{
    float magnitude = GetMagnitude();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

Vec3 operator+(Vec3 v1, Vec3 v2)
{
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vec3 operator*(Vec3 vec, float factor)
{
    return {vec.x * factor, vec.y * factor, vec.z * factor};
}

Vec3 operator-(Vec3 v1, Vec3 v2)
{
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}


Vec3 operator*(Vec3 vec1, Vec3 vec2)
{
    return {vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z};
}