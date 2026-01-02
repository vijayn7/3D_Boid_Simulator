#include "raylib.h"

#include <vector>
#include <cmath>

#include "Constants.cpp"

#include "Boid3D.h"
#include "Vec3D.h"
#include "Drawer3D.h"
#include "BoidManager.h"
#include "BruteForceManager3D.cpp"

int main() {
    
    InitWindow(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Boids 3D - raylib");
    SetTargetFPS(Constants::Target_FPS);

    Camera3D camera = Constants::INITIAL_CAMERA;

    BoidManager* manager = new BruteForceManager();
    Drawer3D drawer = Drawer3D();

    manager->setNumBoids(200);

    while (!WindowShouldClose()) {

        float dt = GetFrameTime();

        UpdateCamera(&camera, CAMERA_FREE);

        manager->updateBoids(dt);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);

        drawer.drawBoundary();

        // Draw boids
        for (Boid3D* b : manager->getBoidsInRange({0.0f, 0.0f, 0.0f}, Constants::WORLD_SIZE)) {
            drawer.drawBoid(*b);
            drawer.drawBoidVelocity(*b);
        }

        EndMode3D();

        DrawText("WASD + mouse to move camera | V: velocity lines | B: bounds", 16, 16, 18, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();

    delete manager;

    return 0;

}