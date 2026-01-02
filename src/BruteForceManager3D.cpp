#include "BoidManager.h"
#include <vector>
#include <cmath>
#include "Vec3D.h"
#include "Boid3D.h"
#include "Constants.h"

class BruteForceManager : public BoidManager {
    std::vector<Boid3D> boids = {};

    static float frand(float min, float max) {
        return min + static_cast<float>(rand()) / RAND_MAX * (max - min);
    }

    void spawnBoid() {
        Boid3D b;
        b.pos = Vec3D{
            frand(-Constants::WORLD_HALF_SIZE, Constants::WORLD_HALF_SIZE),
            frand(-Constants::WORLD_HALF_SIZE, Constants::WORLD_HALF_SIZE),
            frand(-Constants::WORLD_HALF_SIZE, Constants::WORLD_HALF_SIZE)
        };
        b.vel = Vec3D{
            frand(-1.0f, 1.0f),
            frand(-1.0f, 1.0f),
            frand(-1.0f, 1.0f)
        };
        boids.push_back(b);
    }

    public:

    std::vector<Boid3D*> getBoidsInRange(const Vec3D& position, float range) override {
        std::vector<Boid3D*> inRange;
        float rangeSq = range * range;

        for (Boid3D& b : boids) {
            Vec3D diff = b.pos - position;
            if (diff.lengthSquared() <= rangeSq) {
                inRange.push_back(&b);
            }
        }

        return inRange;
    }

    void setNumBoids(const int numBoids) override {
        if (numBoids < boids.size()) {
            boids.resize(numBoids);
        } else {
            while (boids.size() < numBoids) {
                spawnBoid();
            }
        }
    }

    void updateBoids(float dt) override {
        for (Boid3D& b : boids) {
            std::vector<Boid3D*> neighbors = getBoidsInRange(b.pos, Constants::NEIGHBORHOOD_RADIUS);

            Vec3D coh = b.cohesion(neighbors, Constants::MAX_SPEED, Constants::MAX_FORCE) * Constants::COHESION_WEIGHT;
            Vec3D ali = b.alignment(neighbors, Constants::MAX_SPEED, Constants::MAX_FORCE) * Constants::ALIGNMENT_WEIGHT;
            Vec3D sep = b.separation(neighbors, Constants::MAX_FORCE) * Constants::SEPARATION_WEIGHT;

            b.applyForce(coh);
            b.applyForce(ali);
            b.applyForce(sep);

            b.update(dt, Constants::MAX_SPEED);
        }
    }

};