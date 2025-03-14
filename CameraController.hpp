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
};