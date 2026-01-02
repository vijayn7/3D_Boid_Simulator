#pragma once
#include "raylib.h"
#include "Vec3D.h"
#include "Boid3D.h"
#include "Constants.cpp"

class Drawer3D {
    Color boundryColor = DARKGREEN;

    Color boidColor = BLUE;
    Color boidWireColor = DARKBLUE;

    float boidLength = 10.0f;
    float boidRadiusTip = 0.0f;
    float boidRadiusTail = 2.0f;

    float boidVelocityScale = 2.0f;
    Color boidVelocityColor = RED;
    
public:

    void drawBoid(Boid3D b) {
        Vec3D v = b.vel;
        if (v.lengthSquared() < 1e-8f) v = {1,0,0};
        Vec3D dir = normalize(v);

        Vec3D tip  = b.pos + dir * (boidLength * 0.65f);
        Vec3D tail = b.pos - dir * (boidLength * 0.35f);

        DrawCylinderEx(toV3(tail), toV3(tip), boidRadiusTail, boidRadiusTip, 8, boidColor);
    }

    void drawBoidVelocity(Boid3D b) {
        Vec3D velEnd = b.pos + b.vel * boidVelocityScale;
        DrawLine3D(toV3(b.pos), toV3(velEnd), boidVelocityColor);
    }

    void drawBoundary(const Vec3D& center) {
        DrawCubeWires({center.x, center.y, center.z}, Constants::WORLD_SIZE, Constants::WORLD_SIZE, Constants::WORLD_SIZE, boundryColor);
        DrawGrid(20, 2.0f);
    }


    static Vector3 toV3(const Vec3D& v) { return {v.x, v.y, v.z}; }

};