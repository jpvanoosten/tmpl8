#include "game.h"
#include "surface.h"
#include "template.h"
#include <cstdio> //printf

namespace Tmpl8
{
    static constexpr Pixel RED = 0xff0000;
    static constexpr Pixel GREEN = 0x00ff00;
    static constexpr Pixel BLUE = 0x0000ff;
    static constexpr Pixel YELLOW = 0x00ffff;

    struct Line
    {
        vec2 p0, p1; // Begin/end line points.
        Pixel c;	 // Line color.
    };

    const Line code[] = {
        { {120, 180}, { 90, 160 }, RED },
        { { 90, 160}, { 60, 180 }, RED },
        { { 60, 180 }, {60, 300}, RED },
        { { 60, 300 }, { 90, 330 }, RED },
        { { 90, 330 }, { 120, 300}, RED },
        { { 251, 155 }, { 219, 167 }, BLUE },
        { {219, 167 }, { 200, 200 }, BLUE },

    };

    // -----------------------------------------------------------
    // Initialize the application
    // -----------------------------------------------------------
    void Game::Init()
    {
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
        // clear the graphics window
        screen->Clear(0);

        for (auto& line : code)
        {
            screen->Line(line.p0.x, line.p0.y, line.p1.x, line.p1.y, line.c);
        }
    }
};