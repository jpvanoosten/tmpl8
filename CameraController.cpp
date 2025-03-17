#include "CameraController.hpp"
#include "Math.hpp"

#include "template.h"

const float CameraController::offsetX = 0.0f; // Added to the initial player position to "offset" the position of the camera.
const float CameraController::offsetY = -100.0f; // Added to the initial player position to "offset" the position of the camera.
const float CameraController::dampingX = 0.9f; // Damping to apply in the X direction.
const float CameraController::dampingY = 10.0f; // Damping to apply in the Y direction.
const float CameraController::lookAhead = ScreenWidth; // How far to move the camera ahead of the player's direction.
const float CameraController::lookAheadThreshold = 10.0f; // Minimum speed to trigger look-ahead.


CameraController::CameraController(Camera& c, const Player& p)
    : camera{ &c }
    , player{ &p }
{
}

void CameraController::update(float deltaTime)
{
    if (camera == nullptr || player == nullptr) return;

    auto targetPosition = player->getPosition() - Tmpl8::vec2{ ScreenWidth / 2.0f, ScreenHeight / 2.0f } + Tmpl8::vec2{ offsetX, offsetY };
    auto playerVelocity = player->getVelocity();
    auto cameraPosition = camera->getPos();

    if (std::abs(playerVelocity.x) > lookAheadThreshold)
    {
        // Scale the look ahead distance based on the player's current velocity.
        float d = lookAhead * std::abs(playerVelocity.x) / Player::moveSpeed;
        float lookAheadOffset = sign(playerVelocity.x) * d;
        targetPosition.x += lookAheadOffset;
    }

    // Smoothly move camera toward target position (with damping)
    cameraPosition.x = smoothDamp(cameraPosition.x, targetPosition.x, dampingX, deltaTime);
    cameraPosition.y = smoothDamp(cameraPosition.y, targetPosition.y, dampingY, deltaTime);

    camera->setPos(cameraPosition);
}
