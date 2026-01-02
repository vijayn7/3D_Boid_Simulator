#pragma once
#include "Vec3D.h"
#include <vector>
#include <cmath>

class Boid3D {
    public:
    Vec3D pos;
    Vec3D vel;
    Vec3D acc;

    void applyForce(const Vec3D& force) {
        acc += force;
    }

    void update(float dt, float maxSpeed) {
        vel += acc * dt;
        vel = clampMag(vel, maxSpeed);
        pos += vel * dt;
        acc = Vec3D(0, 0, 0);
    }

    // Neighbors are all within neighborhood radius
    Vec3D cohesion(std::vector<Boid3D*>& neighbors, float maxSpeed, float maxForce) {
        
        Vec3D center{0, 0, 0};

        for (Boid3D* b : neighbors) {
            center += b->pos;
        }

        if (neighbors.empty()) return Vec3D(0, 0, 0);

        center /= static_cast<float>(neighbors.size());

        Vec3D desired = center - pos;
        desired = normalize(desired) * maxSpeed;

        Vec3D steer = desired - vel;
        steer = clampMag(steer, maxForce);
        return steer;
    }

    // Neighbors are all within neighborhood radius
    Vec3D alignment(std::vector<Boid3D*>& neighbors, float maxSpeed, float maxForce) {
        
        Vec3D avgVel{0, 0, 0};

        for (Boid3D* b : neighbors) {
            avgVel += b->vel;
        }

        if (neighbors.empty()) return Vec3D(0, 0, 0);

        avgVel /= static_cast<float>(neighbors.size());
        avgVel = normalize(avgVel) * maxSpeed;

        Vec3D steer = avgVel - vel;
        steer = clampMag(steer, maxForce);
        return steer;
    }

    // Neighbors are all within desired separation distance
    Vec3D separation(std::vector<Boid3D*>& neighbors, float maxForce) {
        
        Vec3D steer{0, 0, 0};
        int count = 0;

        for (Boid3D* b : neighbors) {
            Vec3D diff = pos - b->pos;
            float d = diff.length();
            if (d > 0) {
                diff = normalize(diff);
                diff /= d; 
                steer += diff;
                count++;
            }
        }

        if (count > 0) {
            steer /= static_cast<float>(count);
        }

        if (steer.length() > 1e-6f) {
            steer = normalize(steer) * maxForce;
        }

        return steer;
    }
    
};