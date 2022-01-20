#include "game.h"
#include "surface.h"
#include "template.h"
#include "TileMap.h"
#include <SDL_scancode.h>

namespace Tmpl8
{
    float px = 32.0f, py = 32.0f;

    void Game::Init() {}

    void Game::KeyDown(int key)
    {
        switch (key)
        {
        case SDL_SCANCODE_LEFT:
            m_Left = 1.0f;
            break;
        case SDL_SCANCODE_RIGHT:
            m_Right = 1.0f;
            break;
        case SDL_SCANCODE_UP:
            m_Up = 1.0f;
            break;
        case SDL_SCANCODE_DOWN:
            m_Down = 1.0f;
            break;
        default:
            break;
        }
    }

    void Game::KeyUp(int key)
    {
        switch (key)
        {
        case SDL_SCANCODE_LEFT:
            m_Left = 0.0f;
            break;
        case SDL_SCANCODE_RIGHT:
            m_Right = 0.0f;
            break;
        case SDL_SCANCODE_UP:
            m_Up = 0.0f;
            break;
        case SDL_SCANCODE_DOWN:
            m_Down = 0.0f;
            break;
        default:
            break;
        }
    }

    void Game::Shutdown() {}

    Surface tiles("assets/nc2tiles.png");
    Sprite tank(new Surface("assets/ctankbase.tga"), 16);

    char map[5][31] = {
         "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
         "kcXfb fb fb kc kc kc kc kc kc ",
         "kcXfb fb fb fb fb kc kc kc kc ",
         "kcXlcXlc fb fb fb kc kc kc kc ",
         "kcXkcXkcXlcXlcXlcXkcXkcXkc kc "
    };

    void DrawTile(int tx, int ty, Surface* screen, int x, int y)
    {
        Pixel* src = tiles.GetBuffer() + 1 + tx * 33 + (1 + ty * 33) * 595;
        Pixel* dst = screen->GetBuffer() + x + y * 800;
        for (int i = 0; i < 32; i++, src += 595, dst += 800)
            for (int j = 0; j < 32; j++)
                dst[j] = src[j];
    }

    bool CheckPos(int x, int y)
    {
        if (x < 0 || x >= ScreenWidth || y < 0 || y >= ScreenHeight) return false;

        int tx = x / 32, ty = y / 32;
        return map[ty][tx * 3 + 2] != 'X';
    }
    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f;

        screen->Clear(0);
        for (int y = 0; y < 5; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                int tx = map[y][x * 3] - 'a';
                int ty = map[y][x * 3 + 1] - 'a';
                DrawTile(tx, ty, screen, x * 32, y * 32);
            }
        }

        float nx = px + ( m_Right - m_Left ) * deltaTime * 60.0f, ny = py + ( m_Down - m_Up ) * deltaTime * 60.0f;

        if (CheckPos(nx, ny) && CheckPos(nx + 50, ny + 50) && CheckPos(nx + 50, ny) && CheckPos(nx, ny + 50))
            px = nx, py = ny;

        tank.Draw(screen, px, py);

        TileMap tiles("assets/nc2tiles.png", 18, 5);

        auto& tile = tiles[1];
        if (!tile.isBlocking)
        {

        }
    }
};