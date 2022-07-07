#ifndef _VEC4_H_
#define _VEC4_H_

    class Vec3;

    class Vec4
    {
        public:
        Vec4();
        Vec4(const Vec3& vec3);
        ~Vec4();
        Vec4(float x, float y, float z, float w);


        float x;
        float y;
        float z;
        float w;

        void Homogenize();
        float GetMagnitude() const;
        void Normalize();
    };

    Vec4 operator+(Vec4 v1, Vec4 v2);
    
#endif