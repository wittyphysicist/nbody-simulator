// ModifiedGravity.h
#pragma once
#include "GravityModel.h"
#include <cmath>

// Yukawa-screened gravity:
// F = F_Newton * (1 + alpha * exp(-r / lambda))
//
// alpha  : strength of modification (0 = pure Newtonian)
// lambda : screening length scale in metres
//          e.g. 1 AU = 1.496e11 m for solar-system-scale effects

class ModifiedGravity : public GravityModel {
public:
    double G;
    double softening;
    double alpha;   // modification strength
    double lambda;  // screening scale (metres)

    ModifiedGravity(double alpha, double lambda,
                    double G = 6.674e-11, double softening = 1e-5)
        : G(G), softening(softening), alpha(alpha), lambda(lambda) {}

    Vec3 force(const Vec3& r, double m1, double m2) const override {
        double distSq  = r.normSq() + softening * softening;
        double dist    = std::sqrt(distSq);

        // Newtonian base force magnitude
        double mag = G * m1 * m2 / distSq;

        // Yukawa correction factor
        double yukawa = 1.0 + alpha * std::exp(-dist / lambda);

        return r * (mag * yukawa / dist);
    }
};