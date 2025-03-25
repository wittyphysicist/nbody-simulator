# N-Body Gravitational Simulator

A high-performance N-body gravitational simulator written in C++, featuring a
pluggable gravity model system, a symplectic leapfrog integrator, and OpenMP
parallelisation. Built as an extension of Master's thesis research into modified
gravity models and the Hubble tension.

---

## Motivation

My Master's thesis (*Ludwig-Maximilians-Universität München, 2025*) investigated
whether late-time modifications to gravity could resolve the Hubble tension —
the ~5σ discrepancy between early- and late-universe measurements of the Hubble
constant. This simulator brings that research down to the N-body scale: the same
gravity models studied analytically in the thesis can now be applied to particle
simulations and their orbital effects observed directly.

---

## Features

- **Leapfrog (symplectic) integrator** — time-reversible and energy-conserving;
  energy drift < 1e-12% over one simulated year
- **Pluggable gravity models** via abstract base class — swap physics with a
  single line in `main.cpp`
- **Yukawa-screened modified gravity** — parameterised by strength `α` and
  screening scale `λ`, directly motivated by modified gravity research
- **OpenMP parallelisation** of the O(N²) force loop — tested across 10 threads
  on Apple M-series hardware
- **CSV trajectory output** with Python/matplotlib visualisation

---

## Results

### Newtonian vs modified gravity (α=0.1, λ=1 AU)

The Yukawa correction adds an extra attractive force at solar-system scales,
pulling Earth into a tighter orbit. Both simulations conserve energy well.

![Orbit comparison](images/orbit_comparison.png)

| Model | Energy drift (1 year) |
|---|---|
| Newtonian gravity | 9.58 × 10⁻¹³ % |
| Modified gravity (α=0.1, λ=1 AU) | 0.014 % |

### OpenMP performance (Apple M-series, 10 cores)

| Particles | 1 thread | 10 threads | Speedup |
|---|---|---|---|
| 100 | — | — | — |
| 500 | — | — | — |
| 1000 | — | — | — |

*Benchmark in progress — run `scripts/benchmark.sh` to populate.*

---

## Project structure

```
.
├── Vec3.h                  # 3D vector type with operator overloading
├── Particle.h              # Particle class (pos, vel, force, mass)
├── GravityModel.h          # Abstract base class for gravity models
├── NewtonianGravity.h      # Standard 1/r² gravity
├── ModifiedGravity.h       # Yukawa-screened modified gravity
├── Simulation.h            # Leapfrog integrator + OpenMP force loop
├── FileWriter.h            # CSV trajectory output
├── main.cpp                # Entry point — configure and run simulations
├── plot.py                 # Python visualisation (matplotlib)
├── Makefile                # Build system
└── images/                 # Output plots
```

---

## Build and run

### Requirements

- C++17 compiler (g++ or Apple Clang)
- [Homebrew](https://brew.sh) (macOS only, for OpenMP)
- Python 3 with `pandas` and `matplotlib`

### macOS

```bash
brew install libomp
make
./main
```

### Linux

```bash
g++ -O2 -std=c++17 -fopenmp main.cpp -o main
./main
```

### Visualise

```bash
python3 plot.py
```

---

## Gravity models

### NewtonianGravity

Standard inverse-square law with softening to prevent force singularities at
close range:

```
F = G · m₁ · m₂ / (r² + ε²)
```

### ModifiedGravity (Yukawa screening)

Adds a scale-dependent correction motivated by scalar-tensor theories of gravity:

```
F = F_Newton · (1 + α · exp(−r / λ))
```

| Parameter | Meaning | Default |
|---|---|---|
| `α` (alpha) | Modification strength | 0.1 |
| `λ` (lambda) | Screening length (metres) | 1.496e11 (1 AU) |

Setting `α = 0` recovers standard Newtonian gravity exactly.

### Adding a new gravity model

Subclass `GravityModel` and implement one method:

```cpp
class MyGravity : public GravityModel {
public:
    Vec3 force(const Vec3& r, double m1, double m2) const override {
        // your implementation
    }
};
```

Pass it to `Simulation` in `main.cpp`:

```cpp
Simulation sim(std::make_shared<MyGravity>());
```

---

## Background: the Hubble tension

The Hubble constant H₀ — the rate at which the universe is expanding — can be
measured two ways: from the early universe (CMB, giving ~67 km/s/Mpc) and from
the late universe (distance ladder, giving ~73 km/s/Mpc). The ~5σ discrepancy
between these values is one of the most significant open problems in cosmology.

One proposed resolution is that gravity itself behaves differently at late
cosmological times. My thesis used the MGCAMB package and Bayesian inference on
cosmological datasets to constrain such models. This simulator explores the
same class of modifications at the N-body scale.

---

## Author

**Ege Özmeral** — MSc Physics, Ludwig-Maximilians-Universität München  
[linkedin.com/in/ege-ozmeral](https://linkedin.com/in/ege-ozmeral) · [github.com/wittyphysicist](https://github.com/wittyphysicist)
