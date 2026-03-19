// Vec3.h
#pragma once
#include <cmath>

struct Vec3 {
    double x, y, z;

    Vec3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& o) const { return {x+o.x, y+o.y, z+o.z}; }
    Vec3 operator-(const Vec3& o) const { return {x-o.x, y-o.y, z-o.z}; }
    Vec3 operator*(double s)      const { return {x*s,   y*s,   z*s};   }
    Vec3& operator+=(const Vec3& o) { x+=o.x; y+=o.y; z+=o.z; return *this; }

    double dot(const Vec3& o)  const { return x*o.x + y*o.y + z*o.z; }
    double norm()              const { return std::sqrt(dot(*this)); }
    double normSq()            const { return dot(*this); }
};

// Allows: scalar * vec (e.g. 0.5 * velocity)
inline Vec3 operator*(double s, const Vec3& v) { return v * s; }