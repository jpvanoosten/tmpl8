#include "CameraController.hpp"

#include "template.h"

CameraController::CameraController(Camera& c, const Player& p)
    : camera{&c}
    , player{&p}
{}

void CameraController::update(float deltaTime)
{
    if (camera == nullptr || player == nullptr) return;

    // Update camera based on player's x coordinate.
    float deltaX = player->getPosition().x - ScreenWidth / 2.0f;
    camera->setPos({ deltaX, 0 });
}
