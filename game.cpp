#include "game.h"
#include "surface.h"
#include "template.h"
#include "windows.h"

namespace Tmpl8
{
    Surface tiles("assets/nc2tiles.png");
    Sprite tanksprite(new Surface("assets/ctankbase.tga"), 16);

    class Tank
    {
    public:
        Tank(float ix, float iy, float ispeed = 1.5f, int idirection = 0)
        {
            x = ix;
            y = iy;
            direction = idirection;
            speed = ispeed;
        }

        void TurnLeft()
        {
            if (--direction < 0) direction = 15;
        }

        void TurnRight() {
            if (++direction > 15) direction = 0;
        }

        virtual void Think(const Tank& target)
        {
            int i = 3;
        }

        virtual void Move()
        {
            float angle = ((2 * PI) / 16) * direction;
            x += (sinf(angle) * speed);
            y += (-cosf(angle) * speed);
            if (x > ScreenWidth) x = 0;
            if (x < 0) x = ScreenWidth;
            if (y > ScreenHeight) y = 0;
            if (y < 0) y = ScreenHeight;
        }

        void Draw(Surface* gameScreen)
        {
            tanksprite.SetFrame(direction);
            tanksprite.Draw(gameScreen, (int)x, (int)y);
        }

        float x, y;
        int direction;
        float speed;
    };

    class AITank : public Tank
    {
    public:
        AITank(float ix, float iy, int idirection = 0)
            : Tank(ix, iy, 0.5f, idirection) //Make sure the AI Tank is slower than the player 
        {}

        void Think(const Tank& target) override
        {
            if (turn_delay-- <= 0)
            {
                //Current direction of the AITank
                int toright = direction + 4;
                if (toright > 15) toright = 0;
                float angle = ((2 * PI) / 16) * (float)toright;
                float ax = sinf(angle);
                float ay = -cosf(angle);
                //The direction of the target tank relative to this tank
                float bx = (target.x - x);
                float by = (target.y - y);
                float dot_result = ax * bx + ay * by;
                if (dot_result > 0.0f)
                    this->TurnRight();
                else
                    this->TurnLeft();
                turn_delay = rand() % 40;
            }
        }

        void Move() override
        {
            float angle = ((2 * PI) / 16) * direction;
            x += (sinf(angle) * speed);
            y += (-cosf(angle) * speed);
            if (x > 500) x = 500;
            if (x < 100) x = 100;
            if (y > 150) y = 150;
            if (y < 450) y = 450;
        }

        int turn_delay = rand() % 40;
    };

    Tank mytank(64, 64);
    AITank aitank(128, 64);
    float frame_timer = 0.0f;

    void Game::Init() {}
    void Game::Shutdown() {}

    static char map[16][78] = {
        "jb fb fa fb fb fb fb fb fb fb fb fb fb fa fb fb kc kc kc kc kc kc kc kc kc kc",
        "jb fb fa fb fb fb fb fb fb fb fb fb fb fa fb fb kc kc kc kc kc kc kc kc kc kc",
        "jb fb fa fb fb fb fb fb fb fb fb fb fb fa fb fb kc kc kc kc kc kc kc kc kc kc",
        "jb fb ed fe fe fe fe fe fe fe fe fe fe fd fb fb kc kc kc kc kc kc kc kc kc kc",
        "jb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb kc kc kc kc kc kc kc ad kc kc",
        "jb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb kc kc kc kc kc kc kc cb kc kc",
        "jb fb kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc cb kc kc",
        "jb fb kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc cb kc kc",
        "jb fb kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc cb kc kc",
        "jb fb kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc cb kc kc",
        "jb fb kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc db kc kc",
        "jb fb kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc kc",
        "bd cd de cd cd cd cd cd cd cd cd cd de cd cd bc kc kc kc kc kc kc kc kc kc kc",
        "fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb",
        "fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb",
        "fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb fb"
    };

    void DrawTile(int tx, int ty, Surface* screen, int x, int y)
    {
        Pixel* src = tiles.GetBuffer() + 1 + tx * 33 + (1 + ty * 33) * 595;
        Pixel* dst = screen->GetBuffer() + x + y * 800;

        for (int i = 0; i < 32; i++, src += 595, dst += 800)
            for (int j = 0; j < 32; j++)
                dst[j] = src[j];
    }

    void Game::Tick(float deltaTime)
    {
        frame_timer += deltaTime;
        if (frame_timer > 50)
        {
            screen->Clear(0);
            for (int y = 0; y < 16; y++)
                for (int x = 0; x < 25; x++)
                {
                    int tx = map[y][x * 3] - 'a', ty = map[y][x * 3 + 1] - 'a';
                    DrawTile(tx, ty, screen, x * 32, y * 32);
                }
            if (GetAsyncKeyState(VK_LEFT)) { mytank.TurnLeft(); }
            if (GetAsyncKeyState(VK_RIGHT)) { mytank.TurnRight(); }
            mytank.Move();
            aitank.Think(mytank);
            aitank.Move();
            mytank.Draw(screen);
            aitank.Draw(screen);
            frame_timer = 0.0f;
        }
    }
};