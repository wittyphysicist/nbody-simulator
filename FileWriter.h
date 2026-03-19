// FileWriter.h
#pragma once
#include "Simulation.h"
#include <fstream>
#include <string>
#include <stdexcept>

class FileWriter {
public:
    explicit FileWriter(const std::string& filename) {
        file.open(filename);
        if (!file.is_open())
            throw std::runtime_error("Could not open file: " + filename);
        // CSV header
        file << "step,particle,x,y,z,vx,vy,vz\n";
    }

    ~FileWriter() {
        if (file.is_open()) file.close();
    }

    void writeStep(int step, const Simulation& sim) {
        for (size_t i = 0; i < sim.particles.size(); i++) {
            const auto& p = sim.particles[i];
            file << step        << ","
                 << i           << ","
                 << p.pos.x     << ","
                 << p.pos.y     << ","
                 << p.pos.z     << ","
                 << p.vel.x     << ","
                 << p.vel.y     << ","
                 << p.vel.z     << "\n";
        }
    }

private:
    std::ofstream file;
};