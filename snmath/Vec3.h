#ifndef _VEC3_H_
#define _VEC3_H_

#include "Vec4.h"

class Vec3
{
    public:
        Vec3();
        Vec3(const float& x, const float& y, const float& z);
        Vec3(const Vec4& copyVec);
        ~Vec3();

        float x;
        float y;
        float z;
        
        float GetMagnitude() const;
        void Normalize();
        
};

Vec3 operator+(Vec3 v1, Vec3 v2);

Vec3 operator-(Vec3 v1, Vec3 v2);

Vec3 operator*(Vec3 vec, float factor);

Vec3 operator*(Vec3 vec1, Vec3 vec2);



#endif