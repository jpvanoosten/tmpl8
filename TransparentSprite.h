#pragma once

#include <filesystem>

#include "surface.h"
#include "template.h"

class TransparentSprite
{
public:
    TransparentSprite(const std::filesystem::path& spriteSheet, int numFrames);

    void setPosition(float x, float y);
    void setPosition(const Tmpl8::vec2& pos);
    const Tmpl8::vec2& getPosition() const;

    int getWidth() const;
    int getHeight() const;

    void setFrame(int frame);
    int getFrame() const;

    void setAlpha(float alpha);
    float getAlpha() const;

    void render(Tmpl8::Surface& screen);

private:
    const int m_NumFrames = 0;
    Tmpl8::Sprite m_Sprite;
    Tmpl8::vec2 m_Position{0.0f, 0.0f};
    uint m_Frame = 0;
    float m_Alpha = 1.0f;
};

