#pragma once

#include "Camera.hpp"
#include "Player.hpp"

class CameraController
{
public:
    CameraController() = default;
    CameraController(Camera& c, const Player& p);

    void update(float deltaTime);

private:
    Camera* camera = nullptr;
    const Player* player = nullptr;

    static const float offsetX; // Added to the initial player position to "offset" the position of the camera.
    static const float offsetY; // Added to the initial player position to "offset" the position of the camera.
    static const float dampingX; // Damping to apply in the X direction.
    static const float dampingY; // Damping to apply in the Y direction.
    static const float lookAhead; // How far to move the camera ahead of the player's direction.
    static const float lookAheadThreshold; // Minimum speed to trigger look-ahead.
};