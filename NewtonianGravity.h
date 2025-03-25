// NewtonianGravity.h
#pragma once
#include "GravityModel.h"
#include <cmath>

class NewtonianGravity : public GravityModel {
public:
    double G;
    double softening;

    explicit NewtonianGravity(double G = 6.674e-11, double softening = 1e-5)
        : G(G), softening(softening) {}

    Vec3 force(const Vec3& r, double m1, double m2) const override {
        double distSq  = r.normSq() + softening * softening;
        double dist    = std::sqrt(distSq);
        double mag     = G * m1 * m2 / distSq;
        return r * (mag / dist);
    }
};