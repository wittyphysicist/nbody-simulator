#include "Simulation.h"
#include "NewtonianGravity.h"
#include "ModifiedGravity.h"
#include "FileWriter.h"
#include <iostream>
#include <iomanip>
#include <memory>
#include <omp.h>

void runSim(std::shared_ptr<GravityModel> model,
            const std::string& filename) {
    Simulation sim(model);
    sim.addParticle(Particle({0, 0, 0}, {0, 0, 0}, 1.989e30));
    sim.addParticle(Particle({1.496e11, 0, 0}, {0, 29800, 0}, 5.972e24));

    double dt    = 3600.0;
    int    steps = 8760;
    int    every = 24;

    double E0 = sim.kineticEnergy() + sim.potentialEnergy();
    FileWriter writer(filename);
    writer.writeStep(0, sim);

    for (int i = 1; i <= steps; i++) {
        sim.step(dt);
        if (i % every == 0) writer.writeStep(i, sim);
    }

    double drift = (sim.kineticEnergy() + sim.potentialEnergy() - E0)
                   / std::abs(E0) * 100.0;
    std::cout << filename << "  energy drift: " << drift << "%\n";
}

int main() {
    std::cout << "Threads available: " << omp_get_max_threads() << "\n";

    runSim(std::make_shared<NewtonianGravity>(),
           "trajectory_newtonian.csv");

    runSim(std::make_shared<ModifiedGravity>(0.1, 1.496e11),
           "trajectory_modified.csv");

    return 0;
}