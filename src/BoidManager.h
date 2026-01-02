#ifndef BOIDHANDLER_H
#define BOIDHANDLER_H

#include <vector>
#include "Vec3D.h"
#include "Boid3D.h"

class BoidManager {
public:
    virtual ~BoidManager() = default;

    virtual std::vector<Boid3D*> getBoidsInRange(const Vec3D& position, float range) = 0;

    virtual void setNumBoids(const int numBoids) = 0;
};

#endif