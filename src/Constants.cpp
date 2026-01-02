#include <raylib.h>
class Constants {
public:
    static constexpr float WORLD_SIZE = 50.0f;
    static constexpr float WORLD_HALF_SIZE = WORLD_SIZE / 2.0f;
    
    static constexpr float MAX_SPEED = 5.0f;
    static constexpr float MAX_FORCE = 0.1f;

    static constexpr float NEIGHBORHOOD_RADIUS = 10.0f;
    static constexpr float COHESION_WEIGHT = 1.0f;
    static constexpr float ALIGNMENT_WEIGHT = 1.0f;
    static constexpr float SEPARATION_WEIGHT = 1.5f;

    static constexpr int WINDOW_WIDTH = 1200;
    static constexpr int WINDOW_HEIGHT = 800;
    static constexpr int Target_FPS = 360;

    static constexpr Vector3 INITIAL_CAMERA_POSITION = {45.0f, 35.0f, 45.0f};
    static constexpr Vector3 INITIAL_CAMERA_TARGET = {0.0f, 0.0f, 0.0f};
    static constexpr Vector3 INITIAL_CAMERA_UP = {0.0f, 1.0f, 0.0f};
    static constexpr float INITIAL_CAMERA_FOV = 45.0f;
    static constexpr CameraProjection INITIAL_CAMERA_Projection = CAMERA_PERSPECTIVE;

    static constexpr Camera3D INITIAL_CAMERA = {
        .position = INITIAL_CAMERA_POSITION,
        .target = INITIAL_CAMERA_TARGET,
        .up = INITIAL_CAMERA_UP,
        .fovy = INITIAL_CAMERA_FOV,
        .projection = INITIAL_CAMERA_Projection
    };
};