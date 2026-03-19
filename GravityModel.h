// GravityModel.h
#pragma once
#include "Vec3.h"

class GravityModel {
public:
    virtual ~GravityModel() = default;

    // Returns the force vector on particle i due to particle j.
    // r    = displacement vector from i to j
    // m1   = mass of particle i
    // m2   = mass of particle j
    virtual Vec3 force(const Vec3& r, double m1, double m2) const = 0;
};
