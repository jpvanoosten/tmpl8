#pragma once

#include <SDL_mouse.h>

#include "AABB.hpp"
#include "Player.hpp"

#include <vector>

namespace Tmpl8 {

    class Surface;
    class Game
    {
    public:
        void SetTarget(Surface* surface) { screen = surface; }
        void Init();
        void Shutdown();
        void Tick(float deltaTime);
        void MouseUp(int button)
        {
            switch (button)
            {
            case SDL_BUTTON_LEFT:
                isLeftButtonDown = false;
                break;
            case SDL_BUTTON_RIGHT:
                isRightButtonDown = false;
                break;
            }
        }
        void MouseDown(int button)
        {
            switch (button)
            {
            case SDL_BUTTON_LEFT:
                isLeftButtonDown = true;
                break;
            case SDL_BUTTON_RIGHT:
                isRightButtonDown = true;
                break;
            }
            previousMousePos = currentMousePos;
        }
        void MouseMove(int x, int y)
        {
            currentMousePos.x = static_cast<float>(x);
            currentMousePos.y = static_cast<float>(y);
        }

        void KeyUp(int key) { /* implement if you want to handle keys */ }
        void KeyDown(int key) { /* implement if you want to handle keys */ }

    private:
        void checkCollisions();
        bool checkVerticalCollisions(const AABB& collider, AABB& aabb, Tmpl8::vec2& vel);
        bool checkHorizontalCollisions(const AABB& collider, AABB& aabb, Tmpl8::vec2& vel);

        Surface* screen;

        Tmpl8::vec2 previousMousePos;
        Tmpl8::vec2 currentMousePos;
        bool isLeftButtonDown = false;
        bool isRightButtonDown = false;


        std::vector<AABB> colliders; // All the platforms in the level.
        Player player;
    };

}; // namespace Tmpl8