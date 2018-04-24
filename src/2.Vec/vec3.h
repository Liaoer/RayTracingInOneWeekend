#pragma once
#include <iostream>
#include <math.h>
#include <stdlib.h>

class Vec3{
    public:
        float e[3];
    public:
        Vec3() {};
        Vec3(float e0,float e1, float e2) {e[0] = e0; e[1] = e1; e[2] = e2;}
        inline float x() const { return e[0]; }
        inline float y() const { return e[1]; }
        inline float z() const { return e[2]; }
        inline float r() const { return e[0]; }
        inline float g() const { return e[1]; }
        inline float b() const { return e[2]; }

        inline const Vec3 & operator+() const { return *this; }
        inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
        inline float operator[] (int i) const { return e[i]; }
        inline float& operator[] (int i) { return e[i]; }
        inline Vec3& operator+=(const Vec3 & v2);
        inline Vec3& operator*=(const Vec3 & v2);
        inline Vec3& operator-=(const Vec3 & v2);
        inline Vec3& operator/=(const Vec3 & v2);
        inline Vec3& operator*=(const float t);
        inline Vec3& operator/=(const float t);

        inline float length() const {
            return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
        }

        inline float squared_length() const {
            return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
        }

        inline void make_unit_vector();
};
