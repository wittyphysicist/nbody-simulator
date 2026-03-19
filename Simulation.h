// Simulation.h
#pragma once
#include "Particle.h"
#include "GravityModel.h"
#include <vector>
#include <memory>
#include <stdexcept>
#include <omp.h>

class Simulation {
public:
    std::vector<Particle>        particles;
    std::shared_ptr<GravityModel> gravityModel;

    explicit Simulation(std::shared_ptr<GravityModel> model)
        : gravityModel(std::move(model)) {
        if (!gravityModel)
            throw std::runtime_error("GravityModel must not be null");
    }

    void addParticle(const Particle& p) { particles.push_back(p); }

    void step(double dt) {
        computeForces();
        for (auto& p : particles) {
            p.vel += (1.0 / p.mass) * p.force * (dt * 0.5);
            p.pos += p.vel * dt;
        }
        computeForces();
        for (auto& p : particles) {
            p.vel += (1.0 / p.mass) * p.force * (dt * 0.5);
        }
    }

    double kineticEnergy() const {
        double ke = 0;
        for (const auto& p : particles) ke += p.kineticEnergy();
        return ke;
    }

    double potentialEnergy() const {
        double pe = 0;
        for (size_t i = 0; i < particles.size(); i++)
            for (size_t j = i + 1; j < particles.size(); j++) {
                Vec3 r = particles[j].pos - particles[i].pos;
                pe -= 6.674e-11 * particles[i].mass * particles[j].mass / r.norm();
            }
        return pe;
    }

private:
    void computeForces() {
        for (auto& p : particles) p.resetForce();

        size_t n = particles.size();
        int nThreads;

        // First pass: find out how many threads we'll get
        #pragma omp parallel
        {
            #pragma omp single
            nThreads = omp_get_num_threads();
        }

        // One force array per thread — no race conditions
        std::vector<std::vector<Vec3>> threadForces(
            nThreads, std::vector<Vec3>(n, Vec3(0, 0, 0)));

        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            auto& localF = threadForces[tid];

            #pragma omp for schedule(dynamic)
            for (size_t i = 0; i < n; i++) {
                for (size_t j = i + 1; j < n; j++) {
                    Vec3 r = particles[j].pos - particles[i].pos;
                    Vec3 f = gravityModel->force(r,
                                particles[i].mass, particles[j].mass);
                    localF[i] += f;
                    localF[j] += f * -1.0;
                }
            }
        }

        // Reduce: sum all thread-local arrays into particle forces
        for (int t = 0; t < nThreads; t++)
            for (size_t i = 0; i < n; i++)
                particles[i].addForce(threadForces[t][i]);
    }
};
