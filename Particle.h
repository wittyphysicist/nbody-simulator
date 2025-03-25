// Particle.h
#pragma once
#include "Vec3.h"
#include <string>

class Particle {
public:
    Vec3   pos;       // position (AU or metres — pick one and stick to it)
    Vec3   vel;       // velocity
    Vec3   force;     // accumulated force for this timestep
    double mass;

    Particle(Vec3 pos, Vec3 vel, double mass)
        : pos(pos), vel(vel), force(0, 0, 0), mass(mass) {}

    // Call at the start of each timestep before accumulating forces
    void resetForce() {
        force = Vec3(0, 0, 0);
    }

    // Accumulate a force contribution (called once per particle pair)
    void addForce(const Vec3& f) {
        force += f;
    }

    // Kinetic energy: 0.5 * m * v²  — used by EnergyChecker
    double kineticEnergy() const {
        return 0.5 * mass * vel.normSq();
    }

    // Handy for debugging and CSV output
    std::string toString() const {
        return std::to_string(pos.x) + "," +
               std::to_string(pos.y) + "," +
               std::to_string(pos.z);
    }
};