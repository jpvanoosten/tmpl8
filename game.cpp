#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <cmath> // atan2
#include <format>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

#include <SDL_keycode.h>

namespace Tmpl8
{
    Game::Game()
        : m_player("assets/player.png", 32)
    {}

    // -----------------------------------------------------------
    // Initialize the application
    // -----------------------------------------------------------
    void Game::Init()
    {
        m_player.setPosition({ ScreenWidth / 2.0f, ScreenHeight / 2.0f });
    }

    // -----------------------------------------------------------
    // Close down application
    // -----------------------------------------------------------
    void Game::Shutdown()
    {
    }

    // -----------------------------------------------------------
    // Main application tick function
    // -----------------------------------------------------------
    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f; // Convert to seconds

        static float totalTime = 0.0f;
        totalTime += deltaTime;

        // clear the graphics window
        screen->Clear(0x6495ED); // Cornflower blue.

        // print something in the graphics window
        screen->Print("hello world", 2, 2, 0xffffff);

        // Move the player
        bool dash = ((GetAsyncKeyState(VK_SHIFT) | GetAsyncKeyState(VK_SPACE)) & 0x80000) != 0; // Is the Shift or space key pressed?

        float up = m_Up ? 1.0f : 0.0f;
        float down = m_Down ? 1.0f : 0.0f;
        float left = m_Left ? 1.0f : 0.0f;
        float right = m_Right ? 1.0f : 0.0f;
        float boost = dash ? 3.0f : 1.0f;

        vec2 playerPos = m_player.getPosition();
        playerPos += vec2{ right - left, down - up } * deltaTime * 100.0f * boost;

        // Clamp to window bounds.
        playerPos.x = std::clamp<float>(playerPos.x, 0.0f, static_cast<float>( ScreenWidth - m_player.getWidth() ) );
        playerPos.y = std::clamp<float>(playerPos.y, 0.0f, static_cast<float>( ScreenHeight - m_player.getHeight() ) );

        m_player.setPosition(playerPos);

        // Update the frame based on the mouse position.
        vec2 mousePos{ static_cast<float>(m_MouseX), static_cast<float>(m_MouseY) };
        vec2 toMouse = mousePos - (playerPos + vec2{ m_player.getWidth() / 2.0f, m_player.getHeight() / 2.0f });
        float angle = atan2f(toMouse.y, toMouse.x) + PI;
        int frame = static_cast<int>(angle / (2.0f * PI) * 32.0f) % 32;

        // The first frame has the player pointing "up" when the angle is 0.
        // Rotate 8 frames to left to get the player to face "left" when the angle is 0.
        m_player.setFrame(frame - 8);

        // Make the player semi-transparent if the shift key is pressed.
        m_player.setAlpha(dash ? 0.5f : 1.0f);

        // draw the player.
        m_player.render(*screen);
    }

    void Game::KeyDown(int key)
    {
        switch (key)
        {
        case SDL_SCANCODE_UP:
        case SDL_SCANCODE_W:
            m_Up = true;
            break;
        case SDL_SCANCODE_DOWN:
        case SDL_SCANCODE_S:
            m_Down = true;
            break;
        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_A:
            m_Left = true;
            break;
        case SDL_SCANCODE_RIGHT:
        case SDL_SCANCODE_D:
            m_Right = true;
            break;
        }
    }

    void Game::KeyUp(int key)
    {
        switch (key)
        {
        case SDL_SCANCODE_UP:
        case SDL_SCANCODE_W:
            m_Up = false;
            break;
        case SDL_SCANCODE_DOWN:
        case SDL_SCANCODE_S:
            m_Down = false;
            break;
        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_A:
            m_Left = false;
            break;
        case SDL_SCANCODE_RIGHT:
        case SDL_SCANCODE_D:
            m_Right = false;
            break;
        }

    }
};