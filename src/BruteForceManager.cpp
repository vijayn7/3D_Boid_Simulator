#include "BoidManager.h"
#include <vector>
#include <cmath>
#include "Vec3D.h"
#include "Boid3D.h"

class BruteForceManager : public BoidManager {
    std::vector<Boid3D> boids = {};

    void spawnBoid() {
        Boid3D b;
        b.pos = Vec3D{
            static_cast<float>(rand()) / RAND_MAX * 50.0f - 25.0f,
            static_cast<float>(rand()) / RAND_MAX * 50.0f - 25.0f,
            static_cast<float>(rand()) / RAND_MAX * 50.0f - 25.0f
        };
        b.vel = Vec3D{
            static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f,
            static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f,
            static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f
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



};